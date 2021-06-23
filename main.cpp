/*
 * main.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: d-w-h
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

int num_calls_performed = 0;

typedef struct table_element {
    bool is_set = false;
    std::string s = "";
} t_elem;

typedef struct result_element {
    std::string result;
    int left_most_index;
} r_elem;

std::string reverse_string(std::string s) {
    int size = s.length();
    std::string result = s;

    for(int i = 0; i < size; ++i) {
        result[i] = s[size-1-i];
    }

    return result;
}

std::string get_max_palindrome(std::string s, int left, int right, t_elem** m_table) {

    std::string result = s;
    int size = s.length();
    int cut = size / 2;
    bool is_palindrome = false;
    int l = 0;
    int r = size - 1;

    num_calls_performed++;

    if(size == 0) {
        result = "";
        m_table[left][right].is_set = true;
        m_table[left][right].s = result;
        return result;
    }

    if(size == 1) {
        m_table[left][right].is_set = true;
        m_table[left][right].s = result;
        return result;
    }

    if(size == 2) {
        if(result[0] == result[1]) {
            m_table[left][right].is_set = true;
            m_table[left][right].s = result;
            return result;
        }
        else {
            return s.substr(l, 1);
        }
    }

    //Check if current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = size / 2 - 1 + l;
        std::string left_cut = s.substr(l, cut + 1);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            m_table[left][right].is_set = true;
            m_table[left][right].s = result;
            return result;
        }
        else {

        }
    }
    else {
        cut = size / 2 + l;
        std::string left_cut = s.substr(l, cut);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            m_table[left][right].is_set = true;
            m_table[left][right].s = result;
            return result;
        }
    }

    //If current string is not palindrome scan substrings for palindromes
    if(!is_palindrome) {
        std::string string1;
        std::string string2;
        int max_size = -100;
        for(int cut_c = l + 1; cut_c <= r; ++cut_c) {
            std::string substring1 = s.substr(l, cut_c);
            std::string substring2 = s.substr(cut_c, r + 1 - cut_c);

            if(m_table[left][right].is_set) {
                string1 = m_table[left][right].s; }
            else { string1 = get_max_palindrome(substring1, l, cut_c, m_table); }

            if(m_table[left][right].is_set) { string2 = m_table[left][right].s; }
            else { string2 = get_max_palindrome(substring2, cut_c, r + 1, m_table); }

            int size1 = string1.length();
            int size2 = string2.length();
            if(size1 > max_size) {
                max_size = size1;
                result = string1;
            }
            if(size2 > max_size) {
                max_size = size2;
                result = string2;
            }
        }

        //If result is not updated, no palindromes are found
        if(result == s) {

            result = "";

            m_table[left][right].is_set = true;
            m_table[left][right].s = result;

            return result;
        }
    }

    m_table[left][right].is_set = true;
    m_table[left][right].s = result;

    return result;
}

typedef struct string_indices {
    int index_l;
    int index_r;
    bool is_palindrome = false;
} s_indices;

s_indices get_max_palindromei(std::string s, int left, int right, t_elem** m_table) {

    std::string result = s;
    s_indices result_indices = {0,0};
    int size = right - left;
    bool is_palindrome = false;
    int l = left;
    int r = right - 1;
    int cut = (right + left) / 2 - 1;

    num_calls_performed++;

    if((right - left) == 0) {
        result = "";

        return {left, right, true};
    }

    if((right - left) == 1) {
        return {left, right, true};
    }

    if((right - left) == 2) {
        if(result[left] == result[left+1]) {
            return {left, right, true};
        }
        else {
            return {left, left + 1, true};
        }
    }

    //Check if current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = (right + left) / 2 - 1;
        std::string left_cut = s.substr(l, cut + 1);

        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            return {left, right, true};
        }
    }
    else {
        cut = size / 2 + l;
        std::string left_cut = s.substr(l, cut);
        std::cout << "left_cut: " << left_cut << std::endl;
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            return {left, right, true};
        }
    }

    //If current string is not palindrome scan substrings for palindromes
    if(!is_palindrome) {
        std::string string1;
        std::string string2;

        s_indices result_indices1;
        s_indices result_indices2;

        int max_size = -100;

        for(int cut_c = l + 1; cut_c <= r; ++cut_c) {
//            if(m_table[left][right].is_set) { string1 = m_table[left][right].s; }
//            else { string1 = get_max_palindromei(s, l, cut_c, m_table); }
            result_indices1 = get_max_palindromei(s, l, cut_c, m_table);
//            if(m_table[left][right].is_set) { string2 = m_table[left][right].s; }
//            else { string2 = get_max_palindromei(s, cut_c, r + 1, m_table); }
            result_indices2 = get_max_palindromei(s, cut_c, r + 1, m_table);
            int size1 = result_indices1.index_r - result_indices1.index_l;
            int size2 = result_indices2.index_r - result_indices2.index_l;
            if(size1 > max_size && result_indices1.is_palindrome) {
                max_size = size1;
                result_indices = result_indices1;
            }
            if(size2 > max_size && result_indices2.is_palindrome) {
                max_size = size2;
                result_indices = result_indices2;
            }
        }
    }

    result_indices = {left, right, is_palindrome};

    return result_indices;
}

s_indices max_palindromei(std::string s) {

    int size = s.length();

    //Initialize memo_table
    t_elem** m_table = new t_elem*[size+1];
    int left = 0;
    int right = size;
    for(int i = 0; i < size + 1; ++i) {
        m_table[i] = new t_elem[size+1];
    }

    for(int i = 0; i < size + 1; ++i) {
        for(int j = 0; j < size + 1; ++j) {
            m_table[i][j].is_set = false;
            m_table[i][j].s = "";
        }
    }

    return get_max_palindromei(s, left, right, m_table);
}

std::string max_palindrome(std::string s) {

    int size = s.length();

    //Initialize memo_table
    t_elem** m_table = new t_elem*[size+1];
    int left = 0;
    int right = size;
    for(int i = 0; i < size + 1; ++i) {
        m_table[i] = new t_elem[size+1];
    }

    for(int i = 0; i < size + 1; ++i) {
        for(int j = 0; j < size + 1; ++j) {
            m_table[i][j].is_set = false;
            m_table[i][j].s = "";
        }
    }

    return get_max_palindrome(s, left, right, m_table);
}

std::string get_max_palindrome_not_memoized(std::string s, int left, int right) {

    std::string result = s;
    int size = s.length();
    int cut = size / 2;
    bool is_palindrome = false;
    int l = 0;
    int r = size - 1;

    num_calls_performed++;

    if(size == 0) {
        result = "";
        return result;
    }

    if(size == 1) {
        return result;
    }

    if(size == 2) {
        if(result[0] == result[1]) {
            return result;
        }
        else {
            return s.substr(l, 1);
        }
    }

    //Check if current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = size / 2 - 1 + l;
        std::string left_cut = s.substr(l, cut + 1);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            return result;
        }
        else {

        }
    }
    else {
        cut = size / 2 + l;
        std::string left_cut = s.substr(l, cut);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            return result;
        }
    }

    //If current string is not palindrome scan substrings for palindromes
    if(!is_palindrome) {
        std::string string1;
        std::string string2;
        int max_size = -100;
        for(int cut_c = l + 1; cut_c <= r; ++cut_c) {
            std::string substring1 = s.substr(l, cut_c);
            std::string substring2 = s.substr(cut_c, r + 1 - cut_c);

            string1 = get_max_palindrome_not_memoized(substring1, l, cut_c);
            string2 = get_max_palindrome_not_memoized(substring2, cut_c, r + 1);

            int size1 = string1.length();
            int size2 = string2.length();
            if(size1 > max_size) {
                max_size = size1;
                result = string1;
            }
            if(size2 > max_size) {
                max_size = size2;
                result = string2;
            }
        }

        //If result is not updated, no palindromes are found
        if(result == s) {

            result = "";

            return result;
        }
    }

    return result;
}

std::string max_palindrome_not_memoized(std::string s) {

    int left = 0;
    int right = s.length();

    return get_max_palindrome_not_memoized(s, left, right);
}

bool is_palindrome(std::string s) {
    std::string result = s;
    int size = s.length();
    int cut = size / 2;
    bool is_palindrome = false;
    int l = 0;
    int r = size - 1;

    if(size >= 0 && size <= 2) {
        return true;
    }

    //Check if current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = size / 2 - 1 + l;
        std::string left_cut = s.substr(l, cut + 1);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            return is_palindrome = true;
        }
        else {

        }
    }
    else {
        cut = size / 2 + l;
        std::string left_cut = s.substr(l, cut);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            return is_palindrome = true;
        }
    }

    return is_palindrome;
}

std::string get_max_palindrome2(std::string s, int left, int right, t_elem** m_table) {

    std::string result = s;
    int size = s.length();
    int cut = size / 2;
    bool is_palindrome = false;
    int l = 0;
    int r = size - 1;

    num_calls_performed++;

    if(size == 0) {
        m_table[left][right].is_set = true;
        m_table[left][right].s = s;
        std::string result = s;
        return result;
    }

    if(size == 1) {
        result = s;
        m_table[left][right].is_set = true;
        m_table[left][right].s = result;
        return result;
    }

    if(size == 2) {
        if(result[0] == result[1]) {
            result = s;
            m_table[left][right].is_set = true;
            m_table[left][right].s = result;
            return result;
        }
        else {
            result = result.substr(l, 1);
            return result;
        }
    }

    //Check if current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = size / 2 - 1 + l;
        std::string left_cut = s.substr(l, cut + 1);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            m_table[left][right].is_set = true;
            m_table[left][right].s = s;
            return result;
        }
        else {

        }
    }
    else {
        cut = size / 2 + l;
        std::string left_cut = s.substr(l, cut);
        std::string right_cut = s.substr(cut + 1, r - cut);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            m_table[left][right].is_set = true;
            m_table[left][right].s = s;
            return result;
        }
    }

    //If current string is not palindrome scan substrings for palindromes
    if(!is_palindrome) {
        std::string string1;
        std::string string2;

        int max_size = -100;
        for(int cut_c = l + 1; cut_c <= r; ++cut_c) {
            if(cut_c != cut) {
                std::string substring1 = s.substr(l, cut_c);
                std::string substring2 = s.substr(cut_c, r + 1 - cut_c);

                if(m_table[left][right].is_set) { string1 = m_table[left][right].s; }
                else { string1 = get_max_palindrome2(substring1, left, left + cut_c, m_table); }

                if(m_table[left][right].is_set) { string2 = m_table[left][right].s; }
                else { string2 = get_max_palindrome2(substring2, left + cut_c, left + r + 1, m_table); }

                int size1 = string1.length();
                int size2 = string2.length();
                if(size1 > max_size) {
                    max_size = size1;
                    result = string1;
                }
                if(size2 > max_size) {
                    max_size = size2;
                    result = string2;
                }
            }
        }

        //If result is not updated, no palindromes are found
        if(result == s) {

            result = "";

            m_table[left][right].is_set = true;
            m_table[left][right].s = result;

            return result;
        }
    }

    m_table[left][right].is_set = true;
    m_table[left][right].s = result;

    return result;
}

std::string max_palindrome2(std::string s) {

    int size = s.length();

    //Initialize memo_table
    t_elem** m_table2 = new t_elem*[size+1];
    int left = 0;
    int right = size;
    for(int i = 0; i < size + 1; ++i) {
        m_table2[i] = new t_elem[size+1];
    }

    for(int i = 0; i < size + 1; ++i) {
        for(int j = 0; j < size + 1; ++j) {
            m_table2[i][j].is_set = false;
            m_table2[i][j].s = "";
        }
    }

    return get_max_palindrome2(s, left, right, m_table2);
}

int main(int argc, char* argv[]) {

    clock_t start, end;
    double execution_time;

    start = clock();

    std::string s = "cbbd";//"xaabacxcabaaxcabaasdffhxxaabacxcghdabaaxcabaaxxcabaaxxaabacxcabaaxca";
    std::string maximum_palindrome = max_palindrome(s);
    bool is_result_palindrome = is_palindrome(maximum_palindrome);

    end = clock();
    execution_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    std::cout << "max palindrome: " << maximum_palindrome << std::endl;
    std::cout << "num calls performed: " << num_calls_performed << std::endl;
    std::cout << "input size: " << s.length() << std::endl;
    std::cout << "execution time: " << execution_time << std::endl;
    std::cout << "is the result a palindrome: " << is_result_palindrome << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}
