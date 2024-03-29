#ifndef STR_UTIL_DOT_H
#define STR_UTIL_DOT_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

using namespace std;

namespace strUtil {
    string removeNumCharsAtPos(const string& s, int pos, int num);
    string insertAtPos(const string& s, int pos, const string& toInsert);
    // default length (-1) means go until the end
    string getAtPos(const string& s, int pos, int length = -1);
    string substring(const string& s, int start, int end);
    bool isEqualAtPos(const string& s, int pos, const string& target);
    string charToString(char c);
    bool contains(const string& s, const string& subs);
    bool containsAtLeast1Of(const string& s, const vector<string>& v);
    bool beginsWith(const string& s, const string& subs);
    string reverse(const string& s);
    string sort(const string& s);
    bool endsWith(const string& s, const string& subs);
    string removeChars(const string& s, char toRemove, int num);
    string removeSubstrings(const string& s, const string& toRemove, int num);
    // removes everything before (but NOT including, by default) the first occurrence of remBefore in s
    string removeAllBeforeChar(const string& s, char remBefore, bool remCharItself = false);
    // removes everything before (but NOT including, by default) the first occurrence of remBefore in s
    string removeAllBeforeSubstring(const string& s, const string& remBefore, bool remSubItself = false);
    // removes everything after (and including, by default) the first occurrence of remAfter in s
    string removeAllAfterChar(const string& s, char remAfter, bool remCharItself = true);
    // removes everything after (and including, by default) the first occurrence of remAfter in s
    string removeAllAfterSubstring(const string& s, const string& remAfter, bool remSubItself = true);
    // returns the position in s of the first occurrence of c (throws exception if c is not in s)
    int positionOfFirstOccurrence(const string& s, char c);
    // returns the position in s of the first occurrence of sub (throws exception if sub is not in s)
    int positionOfFirstOccurrence(const string& s, const string& sub);
    // returns the position in s of the final occurrence of c (throws exception if c is not in s)
    int positionOfFinalOccurrence(const string& s, char c);
    // returns the position in s of the final occurrence of c (throws exception if c is not in s)
    int positionOfFinalOccurrence(const string& s, const string& sub);
    vector<int> positionsOfAllOccurrences(const string& s, char c);
    vector<int> positionOfAllOccurrences(const string& s, const string& sub);
    vector<int> positionOfAllOccurrencesNoOverlap(const string& s, const string& sub);
    int numOccurrences(const string& s, char c);
    int numOccurrences(const string& s, const string& sub);
    int numOccurrencesNoOverlap(const string& s, const string& sub);
    string removeAllOccurrencesOfChar(const string& s, char c);
    string removeAllOccurrencesOfSubstring(const string& s, const string& sub);
    bool parseBool(const string& s);
    string boolval(bool b);
    // requires matching open/close delimiters and no nested delimiters, also requires open delimiter to be different from close delimiter
    // if delimiters are not matched, may run with unexpected results OR throw runtime_error
    // (generally, missing open delimiters will run with unexpected results, while missing close delimiters will throw)
    // if delimiters are nested, may still run but will produce unexpected results
    // if open delimiter and close delimiter are the same character, may still run but will produce unexpected results
    // MORAL: JUST FOLLOW THE REQUIREMENTS!
    // common delimiter pairs used: {} () [] <>
    vector<string> partsSplitByOpenCloseDelimiters(const string& s, char openDelimiter, char closeDelimiter);
    // requires matching open/close delimiters and no nested delimiters, also requires open delimiter to be different from close delimiter
    // if delimiters are not matched, may run with unexpected results OR throw runtime_error
    // (generally, missing open delimiters will run with unexpected results, while missing close delimiters will throw)
    // if delimiters are nested, may still run but will produce unexpected results
    // if open delimiter and close delimiter are the same string, may still run but will produce unexpected results
    // MORAL: JUST FOLLOW THE REQUIREMENTS!
    // common delimiter pairs used: {/} (/) [/] </> {{/}} ((/)) [[/]] <</>>
    vector<string> partsSplitByOpenCloseDelimiters(const string& s, const string& openDelimiter, const string& closeDelimiter);
    void replaceAllChar1WithChar2(string& s, char char1, char char2);
    void replaceAllSub1WithSub2(string& s, const string& sub1, const string& sub2);
    string spaces(int n);
    // returns 0 if v is empty
    int maxStringLength(const vector<string>& v);
    // returns 0 if v is empty
    int minStringLength(const vector<string>& v);
    string removeLeadingCharacters(const string& s, char c);
    string removeLeadingSubstrings(const string& s, const string& sub);
    string removeTrailingCharacters(const string& s, char c);
    string removeTrailingSubstrings(const string& s, const string& sub);
    string removeLeadingSpaces(const string& s);
    string removeTrailingSpaces(const string& s);
    string trim(const string& s);
    bool containsIgnoreLeadingSpaces(const vector<string>& v, const string& s);
    bool containsIgnoreTrailingSpaces(const vector<string>& v, const string& s);
    bool containsTrimmed(const vector<string>& v, const string& s);
    vector<string> fillSpacesTo(const vector<string>& v, int size);
    vector<string> fillSpacesToMaxPlusN(const vector<string>& v, int n = 0);
    string quotify(const string& s);
    vector<string> quotify(const vector<string>& v);
    vector<string> spaceSplit(const string& s);
    string toUpper(const string& s);
    string toLower(const string& s);
    bool equalsIgnoreCase(const string& s1, const string& s2);
    bool isLetter(char c);
    bool isLowerCaseLetter(char c);
    bool isUpperCaseLetter(char c);
    bool isDigit(char c);
    // separates a string into a list of words and spaces/punctuation, ex. "I am. Are you?" -> {"I", " ", "am", ". ", "Are", " ", "you", "?"} 
    vector<string> separateIntoWordsAndSpaces(const string& s);
    vector<int> getAsciiFromString(const string& s);
    vector<char> toCharVector(const string& s);
    string fromCharVector(const vector<char>& v);
    vector<string> split(const string& s, const string& delimiter);
    string join(const vector<string>& v, const string& delimiter = "");
}

#endif