//
// Created by Iron Tony on 26/11/2020.
//

#ifndef MOOP_ATM_VALIDATORS_H
#define MOOP_ATM_VALIDATORS_H

constexpr const char* userNameRegex = R"(^[a-zA-Z]{3,} [a-zA-Z]{3,}$)";
constexpr const char* phoneRegex = R"(^\d{8,16}$)";
constexpr const char* taxRegex = R"(^([A-Z]{2})?\d{8}$)";
constexpr const char* incomeRegex = R"(^[1-9]\d{3,}$)";
constexpr const char* pinRegex = R"(^\d{4}$)";
constexpr const char* cardNumberRegex = R"(^\d{16}$)";
constexpr const char* amountRegex = R"(^[1-9]\d{1,}$)";
constexpr const char* objectNameRegex= ".+";

#endif //MOOP_ATM_VALIDATORS_H
