#pragma once

#include <au/mod.hpp>

#include <imgui.h>

#include <array>
#include <set>
#include <utility>
#include <vector>
#include <random>

namespace au
{
    struct PlayerTask;
} // au

namespace tmg
{
    enum class letter_placement{ none, missing, good, wrong };

    struct letter
    {
        std::string value;
        letter_placement placement = letter_placement::none;
    };
} // tmg

namespace tmg
{
    namespace color
    {
        static ImColor blue{ 8, 76, 97 };
        static ImColor blue_dark{ 28, 36, 67 };
        static ImColor current{ 80, 120, 150 };
        static ImColor red{ 219, 58, 52 };
        static ImColor yellow{ 247, 183, 53 };
    }

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
            tried_letters_.clear();
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

            for (int i = 0; i < attempt.size(); ++i)
            {
                auto placement = letter_placement::missing;
                if (word_[i] == attempt[i])
                {
                    // erase to replace previously wrong placement
                    placement = letter_placement::good;
                    tried_letters_.erase(tmg::letter{ std::string{ attempt[i] } });
                }
                else if (word_.contains(attempt[i])) placement = letter_placement::wrong;
                auto letter = std::string(1, attempt[i]);
                tried_letters_.insert(tmg::letter{ std::string{ attempt[i] }, placement });
            }

            attempts_.emplace_back(attempt, word_);
            if (attempts_.size() >= max_attemps) end();
            input_.clear();
            input_ += word_[0];
        }

        tmg::letter tried_letter(const std::string& letter)
        {
            auto it = std::find_if(tried_letters_.begin(), tried_letters_.end(), [&letter](const auto& tmg_letter) { return tmg_letter.value == letter; });
            if (it == tried_letters_.end()) return tmg::letter{ letter };
            return *it;
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

            if (max_word_size < 6) max_word_size = 6;
            if (max_word_size > 10) max_word_size = 10;

            auto* gwords = &words6;
            std::uniform_int_distribution<> size_index(6, max_word_size);
            auto index = size_index(gen);
            if (index == 7) gwords = &words7;
            if (index == 8) gwords = &words8;
            if (index == 9) gwords = &words9;
            if (index == 10) gwords = &words10;

            std::uniform_int_distribution<> gword_index(0, gwords->size() - 1);
            word_ = (*gwords)[gword_index(gen)];
        }

        //
        std::string ui_buffer;

        // settings
        int max_word_size = 0;

    private:
        static std::vector<std::string> words6;
        static std::vector<std::string> words7;
        static std::vector<std::string> words8;
        static std::vector<std::string> words9;
        static std::vector<std::string> words10;
        std::vector<std::string> words_; // dictionary words

        au::mod& mod_;

        bool active_ = false;
        au::PlayerTask* task_ = nullptr;
        bool has_won_ = false;
        std::string input_;
        std::string word_;
        std::vector<tmg::word> attempts_;

        static inline auto compare_letter = [](auto& lhs, auto& rhs) { return lhs.value < rhs.value; };
        std::set<tmg::letter, decltype(compare_letter)> tried_letters_{ compare_letter };
    };
} // tmg