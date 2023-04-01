#pragma once

#include <array>
#include <vector>
#include <random>

#include <au/mod.hpp>

namespace au
{
    struct PlayerTask;
} // au

namespace tmg
{
    class tusmo
    {
    public:
        inline static int max_attemps = 6;

        tusmo(au::mod& mod) : mod_{ mod }
        {
            words_.emplace_back("CHOUETTE");
            words_.emplace_back("TEST");
            words_.emplace_back("POMPOM");
        }

        void update_input(char key)
        {
            if (input_.size() >= word_.size()) return;
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
        std::string attempt_letter(int x, int y) { return attempts_[y].substr(x, 1); }
        bool is_attempt_letter_red(int x, int y)
        {
            return y < attempts_.size()
                   && x < attempts_[y].size()
                   && attempts_[y][x] == word_[x];
        }
        bool is_attempt_letter_yellow(int x, int y)
        {
            if (y < attempts_.size() && x < attempts_[y].size())
            {
                auto letter = attempts_[y][x];
                if (word_.contains(letter) && attempts_[y][x] != word_[x]) return true;
            }
            return false;
        }

        bool active() const { return active_; }
        const std::string& input() const { return input_; }
        const std::string& word() const { return word_; }
        const std::vector<std::string>& attempts() const { return attempts_; }
        au::PlayerTask* task() const { return task_; }

        void try_word(const std::string& attempt)
        {
            if (attempt.size() != word_.size()) return;

            mod_.log("Try {} -- {}", attempt, word_);
            if (attempt == word_) return end(true);

            attempts_.emplace_back(attempt);
            if (attempts_.size() >= max_attemps) end();
            input_.clear();
            input_ += word_[0];
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
            std::uniform_int_distribution<> word_index(0, words_.size() - 1);
            word_ = words_[word_index(gen)];
        }

        //
        std::string ui_buffer;

    private:
        au::mod& mod_;

        bool active_ = false;
        au::PlayerTask* task_ = nullptr;
        bool has_won_ = false;
        std::string input_;
        std::string word_;
        std::vector<std::string> attempts_;
        std::vector<std::string> words_;
        std::vector<std::string> dicos_;
    };
} // tmg