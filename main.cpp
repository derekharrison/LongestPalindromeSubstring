/*
 * main.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: d-w-h
 */

#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

int num_calls_performed = 0;

typedef struct table_element {
    bool is_set = false;
    std::string s = "";
} t_elem;

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
            return "";
        }
    }

    //Check is current string is palindrome
    bool is_even = !(size % 2);
    if(is_even) {
        cut = size / 2 - 1 + l;
        std::string left_cut = s.substr(l, cut + 1);
        std::string right_cut = s.substr(cut + 1, r);
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
        std::string right_cut = s.substr(cut + 1, r);
        std::string right_cut_reverse = reverse_string(right_cut);

        if(left_cut == right_cut_reverse) {
            is_palindrome = true;
            m_table[left][right].is_set = true;
            m_table[left][right].s = result;
            return result;
        }
    }

    if(!is_palindrome) {
        std::string string1;
        std::string string2;
        int max_size = -100;
        for(int cut_c = l + 1; cut_c <= r; ++cut_c) {
            std::string substring1 = s.substr(l, cut_c);
            std::string substring2 = s.substr(cut_c, r + 1 - cut_c);

            if(m_table[left][right].is_set) { string1 = m_table[left][right].s; }
            else { string1 = get_max_palindrome(s.substr(l, cut_c), l, cut_c, m_table); }

            if(m_table[left][right].is_set) { string2 = m_table[left][right].s; }
            else { string2 = get_max_palindrome(s.substr(cut_c, r + 1 - cut_c), cut_c, r + 1, m_table); }

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

int main(int argc, char* argv[]) {

    std::string s = "xaabacxcabaaxcabaasdffhxxaabacxcabaaxcabaaxxcabaaxxaabacxcabaaxca";
    std::string maximum_palindrome = max_palindrome(s);

    std::cout << "max palindrome: " << maximum_palindrome << std::endl;
    std::cout << "num calls performed: " << num_calls_performed << std::endl;
    std::cout << "input size: " << s.length() << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}
