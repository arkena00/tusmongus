#pragma once

#include <au/mod.hpp>

#include <imgui.h>

#include <array>
#include <utility>
#include <vector>
#include <random>

namespace au
{
    struct PlayerTask;
} // au

namespace tmg
{
    namespace color
    {
        static ImColor blue{8, 76, 97};
        static ImColor current{80, 120, 150};
        static ImColor red{219, 58, 52};
        static ImColor yellow{247, 183, 53};
    }

    enum class letter_placement{ none, good, wrong };

    class word
    {
    public:
        word(std::string attempt, const std::string& source)
            : attempt_{std::move(attempt)}
        {
            std::unordered_map<char, int> letters_remaining_;
            for (int i = 0; i < source.size(); ++i)
            {
                letter_placement placement = letter_placement::none;
                ++letters_remaining_[source[i]];
                if (source[i] == attempt_[i])
                {
                    placement = letter_placement::good;
                    --letters_remaining_[source[i]];
                }

                placement_.emplace_back(placement);
            }

            // handle wrong placement
            for (int i = 0; i < source.size(); ++i)
            {
                auto& letter_remaining_count = letters_remaining_[attempt_[i]];
                if (placement_[i] != letter_placement::good && letter_remaining_count > 0 && source.find(attempt_[i]) != std::string::npos)
                {
                    placement_[i] = letter_placement::wrong;
                    --letter_remaining_count;
                }
            }
        }

        auto placement(int i) const { return placement_[i]; }
        auto letter(int i) const { return attempt_.substr(i, 1); }
        auto size() const { return attempt_.size(); }

    private:
        std::string attempt_;
        std::vector<letter_placement> placement_;
    };

    class tusmo
    {
    public:
        inline static int max_attemps = 6;
        ImFont* font = nullptr;

        tusmo(au::mod& mod);

        void update_input(char key)
        {
            if (input_.size() >= word_.size() || (key == word_[0] && input_.size() == 1)) return;
            input_ += key;
        }
        void erase()
        {
            if (input_.size() > 1) input_.resize(input_.size() - 1);
        }

        void begin(au::PlayerTask* task)
        {
            if (active_) return;

            task_ = task;
            has_won_ = false;
            attempts_.clear();
            input_.clear();
            select_word();
            input_ += word_[0];
            active_ = true;
        }

        std::string letter(int i) { return word_.substr(i, 1); }
        std::string input_letter(int i) { return input_.substr(i, 1); }
        std::string word_letter(int i) { return word_.substr(i, 1); }
        std::string attempt_letter(int x, int y) { return attempts_[y].letter(x); }

        bool active() const { return active_; }
        const std::string& input() const { return input_; }
        const std::string& word() const { return word_; }
        const tmg::word& attempt(int i) const { return attempts_[i]; }
        const std::vector<tmg::word>& attempts() const { return attempts_; }
        au::PlayerTask* task() const { return task_; }

        void try_word(const std::string& attempt)
        {
            if (attempt.size() != word_.size()) return;

            if (attempt == word_) return end(true);

            if (!word_exist(attempt))
            {
                input_ = word_[0];
                return;
            }

            attempts_.emplace_back(attempt, word_);
            if (attempts_.size() >= max_attemps) end();
            input_.clear();
            input_ += word_[0];
        }

        bool word_exist(const std::string& word)
        {
            if (std::find(words_.begin(), words_.end(), word) != words_.end()) return true;
            return false;
        }

        void end(bool has_win = false)
        {
            has_won_ = has_win;
            active_ = false;
        }

        bool ended() { return !active_ || attempts_.size() == max_attemps; }

        bool won() const { return has_won_; }

        void select_word()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> word_index(0, guessable_words.size() - 1);
            word_ = guessable_words[word_index(gen)];
        }

        //
        std::string ui_buffer;

    private:
        static std::vector<std::string> guessable_words;
        std::vector<std::string> words_;

        au::mod& mod_;

        bool active_ = false;
        au::PlayerTask* task_ = nullptr;
        bool has_won_ = false;
        std::string input_;
        std::string word_;
        std::vector<tmg::word> attempts_;
    };
} // tmg