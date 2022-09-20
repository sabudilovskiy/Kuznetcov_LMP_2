#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
struct cords{
    size_t x;
    size_t y;
};

std::set<size_t> task_r(std::vector<std::vector<bool>>& matrix, std::vector<size_t>& path, size_t end){
    size_t n = matrix.size();
    size_t cur_end = path[path.size() - 1];
    if (cur_end != end){
        std::set<size_t> answer;
        for (int i = 0; i < n; ++i){
            if (matrix[cur_end][i] && std::find(path.begin(), path.end(), i) == path.end()){
                path.push_back(i);
                auto result_i = task_r(matrix, path, end);
                if (!result_i.empty()){
                    if (answer.empty()){
                        answer = result_i;
                    }
                    else{
                        std::set<size_t> answer_result_i;
                        for (auto i: result_i){
                            if (std::find(answer.begin(),  answer.end(), i) != answer.end())
                            {
                                answer_result_i.insert(i);
                            }
                        }
                        answer = answer_result_i;
                    }
                }
                path.pop_back();
            }
        }
        return answer;
    }
    else{
        std::set<size_t> answer;
        for (auto i : path){
            answer.insert(i);
        }
        return answer;
    }
}

std::set<size_t> task(std::vector<std::vector<bool>>& matrix, size_t begin, size_t end){
    std::vector<size_t> path;
    path.push_back(begin);
    auto answer = task_r(matrix, path, end);
    answer.erase(begin);
    answer.erase(end);
    return answer;
}

int main() {
    std::vector<std::vector<bool>> matrix;
    std::ifstream file_in("in.txt");
    if (!file_in.eof() && file_in.is_open()){
        size_t n;
        file_in >> n;
        matrix.resize(n);
        for (int i = 0 ;i < n; ++i){
            matrix[i].resize(n);
        }
        while (!file_in.eof()){
            size_t left, right;
            file_in >> left >> right;
            matrix[left][right] = true;
        }
        std::cout << "begin: ";
        size_t begin, end;
        std::cin >> begin;
        std::cout << "end: ";
        std::cin >> end;
        auto answer = task(matrix, begin, end);
        if (answer.empty()){
            std::cout << "No answers";
        }
        else{
            std::cout << "Answers: ";
            for (auto i : answer){
                std::cout << i << ' ';
            }
        }
    }
}
