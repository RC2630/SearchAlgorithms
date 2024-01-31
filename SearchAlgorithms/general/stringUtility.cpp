#include "stringUtility.h"

string strUtil::removeNumCharsAtPos(const string& s, int pos, int num) {
    if (pos < 0 || pos >= s.size()) {
        throw runtime_error("pos out of range");
    } else if (num < 0 || pos + num > s.size()) {
        throw runtime_error("num out of range or too many characters");
    }
    string newString;
    for (int i = 0; i < pos; i++) {
        newString += s.at(i);
    }
    for (int i = pos + num; i < s.size(); i++) {
        newString += s.at(i);
    }
    return newString;
}

string strUtil::insertAtPos(const string& s, int pos, const string& toInsert) {
    if (pos < 0 || pos > s.size()) {
        throw runtime_error("pos out of range");
    }
    string newString = s;
    newString.insert(newString.begin() + pos, toInsert.begin(), toInsert.end());
    return newString;
}

// default length (-1) means go until the end
string strUtil::getAtPos(const string& s, int pos, int length) {
    if (length == -1) {
        length = s.size() - pos;
    }
    if (pos < 0 || pos >= s.size()) {
        throw runtime_error("pos out of range");
    } else if (length < 0 || pos + length > s.size()) {
        throw runtime_error("length is too long");
    } else {
        return s.substr(pos, length);
    }
}

string strUtil::substring(const string& s, int start, int end) {
    if (start < 0 || start >= s.size()) {
        throw runtime_error("start out of range");
    } else if (end < start || end >= s.size()) {
        throw runtime_error("end out of range or before start");
    } else {
        return s.substr(start, end - start + 1);
    }
}

bool strUtil::isEqualAtPos(const string& s, int pos, const string& target) {
    try {
        return getAtPos(s, pos, target.size()) == target;
    } catch (const runtime_error& e) {
        return false;
    }
}

string strUtil::charToString(char c) {
    return string(1, c);
}

bool strUtil::contains(const string& s, const string& subs) {
    return s.find(subs) != string::npos;
}

bool strUtil::containsAtLeast1Of(const string& s, const vector<string>& v) {
    for (const string& e : v) {
        if (contains(s, e)) {
            return true;
        }
    }
    return false;
}

bool strUtil::beginsWith(const string& s, const string& subs) {
    return s.find(subs) == 0;
}

string strUtil::reverse(const string& s) {
    string reversed = s;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

string strUtil::sort(const string& s) {
    string sorted = s;
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

bool strUtil::endsWith(const string& s, const string& subs) {
    return beginsWith(reverse(s), reverse(subs));
}

string strUtil::removeChars(const string& s, char toRemove, int num) {
    string newString;
    for (char c : s) {
        if (c == toRemove && num > 0) {
            // nothing appended to newString
            num--;
        } else {
            newString += c;
        }
    }
    return newString;
}

string strUtil::removeSubstrings(const string& s, const string& toRemove, int num) {
    string newString = s;
    while (contains(newString, toRemove)) {
        for (int i = 0; i < newString.size(); i++) {
            if (isEqualAtPos(newString, i, toRemove)) {
                newString = removeNumCharsAtPos(newString, i, toRemove.size());
                num--;
                i--; // no increment when this happens (this decrement cancels out the loop's increment)
            }
            if (num == 0) {
                return newString;
            }
        }
    }
    return newString;
}

// removes everything before (but NOT including, by default) the first occurrence of remBefore in s
string strUtil::removeAllBeforeChar(const string& s, char remBefore, bool remCharItself) {
    if (!contains(s, charToString(remBefore))) {
        return s;
    }
    if (remCharItself) {
        return s.substr(positionOfFirstOccurrence(s, remBefore) + 1);
    } else {
        return s.substr(positionOfFirstOccurrence(s, remBefore));
    }
}

// removes everything before (but NOT including, by default) the first occurrence of remBefore in s
string strUtil::removeAllBeforeSubstring(const string& s, const string& remBefore, bool remSubItself) {
    if (!contains(s, remBefore)) {
        return s;
    }
    if (remSubItself) {
        return s.substr(positionOfFirstOccurrence(s, remBefore) + remBefore.size());
    } else {
        return s.substr(positionOfFirstOccurrence(s, remBefore));
    }
}

// removes everything after (and including, by default) the first occurrence of remAfter in s
string strUtil::removeAllAfterChar(const string& s, char remAfter, bool remCharItself) {
    if (!contains(s, charToString(remAfter))) {
        return s;
    }
    string newString;
    for (char c : s) {
        if (c != remAfter) {
            newString += c;
        } else {
            break;
        }
    }
    if (remCharItself) {
        return newString;
    } else {
        return newString + remAfter;
    }
}

// removes everything after (and including, by default) the first occurrence of remAfter in s
string strUtil::removeAllAfterSubstring(const string& s, const string& remAfter, bool remSubItself) {
    if (!contains(s, remAfter)) {
        return s;
    }
    if (remSubItself) {
        return s.substr(0, positionOfFirstOccurrence(s, remAfter));
    } else {
        return s.substr(0, positionOfFirstOccurrence(s, remAfter) + remAfter.size());
    }
}

// returns the position in s of the first occurrence of c (throws exception if c is not in s)
int strUtil::positionOfFirstOccurrence(const string& s, char c) {
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == c) {
            return i;
        }
    }
    throw runtime_error(string() + "'" + c + "' is not in \"" + s + "\"");
}

// returns the position in s of the first occurrence of sub (throws exception if sub is not in s)
int strUtil::positionOfFirstOccurrence(const string& s, const string& sub) {
    for (int i = 0; i < s.size(); i++) {
        if (isEqualAtPos(s, i, sub)) {
            return i;
        }
    }
    throw runtime_error(string() + "\"" + sub + "\" is not in \"" + s + "\"");
}

// returns the position in s of the final occurrence of c (throws exception if c is not in s)
int strUtil::positionOfFinalOccurrence(const string& s, char c) {
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s.at(i) == c) {
            return i;
        }
    }
    throw runtime_error(string() + "'" + c + "' is not in \"" + s + "\"");
}

// returns the position in s of the final occurrence of c (throws exception if c is not in s)
int strUtil::positionOfFinalOccurrence(const string& s, const string& sub) {
    for (int i = s.size() - 1; i >= 0; i--) {
        if (isEqualAtPos(s, i, sub)) {
            return i;
        }
    }
    throw runtime_error(string() + "\"" + sub + "\" is not in \"" + s + "\"");
}

vector<int> strUtil::positionsOfAllOccurrences(const string& s, char c) {
    vector<int> positions;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == c) {
            positions.push_back(i);
        }
    }
    return positions;
}

vector<int> strUtil::positionOfAllOccurrences(const string& s, const string& sub) {
    vector<int> positions;
    for (int i = 0; i < s.size(); i++) {
        if (isEqualAtPos(s, i, sub)) {
            positions.push_back(i);
        }
    }
    return positions;
}

vector<int> strUtil::positionOfAllOccurrencesNoOverlap(const string& s, const string& sub) {
    vector<int> positions;
    for (int i = 0; i < s.size();) {
        if (isEqualAtPos(s, i, sub)) {
            positions.push_back(i);
            i += sub.size();
        } else {
            i++;
        }
    }
    return positions;
}

int strUtil::numOccurrences(const string& s, char c) {
    return count(s.begin(), s.end(), c);
}

int strUtil::numOccurrences(const string& s, const string& sub) {
    return positionOfAllOccurrences(s, sub).size();
}

int strUtil::numOccurrencesNoOverlap(const string& s, const string& sub) {
    return positionOfAllOccurrencesNoOverlap(s, sub).size();
}

string strUtil::removeAllOccurrencesOfChar(const string& s, char c) {
    return removeChars(s, c, numOccurrences(s, c));
}

string strUtil::removeAllOccurrencesOfSubstring(const string& s, const string& sub) {
    return removeSubstrings(s, sub, s.size());
}

bool strUtil::parseBool(const string& s) {
    return s == "true" || s == "True" || s == "TRUE";
}

string strUtil::boolval(bool b) {
    return b ? "true" : "false";
}

// requires matching open/close delimiters and no nested delimiters, also requires open delimiter to be different from close delimiter
// if delimiters are not matched, may run with unexpected results OR throw runtime_error
// (generally, missing open delimiters will run with unexpected results, while missing close delimiters will throw)
// if delimiters are nested, may still run but will produce unexpected results
// if open delimiter and close delimiter are the same character, may still run but will produce unexpected results
// MORAL: JUST FOLLOW THE REQUIREMENTS!
// common delimiter pairs used: {} () [] <>
vector<string> strUtil::partsSplitByOpenCloseDelimiters(const string& s, char openDelimiter, char closeDelimiter) {
    vector<string> parts;
    if (!contains(s, charToString(openDelimiter))) {
        parts.push_back(s);
        return parts;
    }
    string currentString;
    int i = 0;
    while (true) {
        if (s.at(i) == openDelimiter) {
            for (int r = i; true; r++) {
                if (r >= s.size()) {
                    string errorMessage = "mismatched delimiters - no closing delimiter ";
                    errorMessage += closeDelimiter;
                    errorMessage += " found";
                    throw runtime_error(errorMessage);
                }
                currentString += s.at(r);
                if (s.at(r) == closeDelimiter) {
                    i = r + 1;
                    parts.push_back(currentString);
                    currentString = "";
                    break;
                }
            }
        } else {
            for (int r = i; true; r++) {
                if (r < s.size() && s.at(r) != openDelimiter) {
                    currentString += s.at(r);
                } else {
                    i = r;
                    parts.push_back(currentString);
                    currentString = "";
                    break;
                }
            }
        }
        if (i >= s.size()) {
            break;
        }
    }
    return parts;
}

// requires matching open/close delimiters and no nested delimiters, also requires open delimiter to be different from close delimiter
// if delimiters are not matched, may run with unexpected results OR throw runtime_error
// (generally, missing open delimiters will run with unexpected results, while missing close delimiters will throw)
// if delimiters are nested, may still run but will produce unexpected results
// if open delimiter and close delimiter are the same string, may still run but will produce unexpected results
// MORAL: JUST FOLLOW THE REQUIREMENTS!
// common delimiter pairs used: {/} (/) [/] </> {{/}} ((/)) [[/]] <</>>
vector<string> strUtil::partsSplitByOpenCloseDelimiters(const string& s, const string& openDelimiter, const string& closeDelimiter) {
    vector<string> parts;
    if (!contains(s, openDelimiter)) {
        parts.push_back(s);
        return parts;
    }
    string currentString;
    int i = 0;
    while (true) {
        if (isEqualAtPos(s, i, openDelimiter)) {
            currentString += openDelimiter;
            for (int r = i + openDelimiter.size(); true; r++) {
                if (r >= s.size()) {
                    string errorMessage = "mismatched delimiters - no closing delimiter ";
                    errorMessage += closeDelimiter;
                    errorMessage += " found";
                    throw runtime_error(errorMessage);
                }
                if (isEqualAtPos(s, r, closeDelimiter)) {
                    i = r + closeDelimiter.size();
                    currentString += closeDelimiter;
                    parts.push_back(currentString);
                    currentString = "";
                    break;
                }
                currentString += s.at(r);
            }
        } else {
            for (int r = i; true; r++) {
                if (r < s.size() && !isEqualAtPos(s, r, openDelimiter)) {
                    currentString += s.at(r);
                } else {
                    i = r;
                    parts.push_back(currentString);
                    currentString = "";
                    break;
                }
            }
        }
        if (i >= s.size()) {
            break;
        }
    }
    return parts;
}

void strUtil::replaceAllChar1WithChar2(string& s, char char1, char char2) {
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == char1) {
            s.at(i) = char2;
        }
    }
}

void strUtil::replaceAllSub1WithSub2(string& s, const string& sub1, const string& sub2) {
    while (contains(s, sub1)) {
        for (int i = 0; i < s.size(); i++) {
            if (isEqualAtPos(s, i, sub1)) {
                removeNumCharsAtPos(s, i, sub1.size());
                insertAtPos(s, i, sub2);
            }
        }
    }
}

string strUtil::spaces(int n) {
    string s;
    for (int i = 1; i <= n; i++) {
        s += " ";
    }
    return s;
}

// returns 0 if v is empty
int strUtil::maxStringLength(const vector<string>& v) {
    int max = 0;
    for (const string& s : v) {
        if (s.size() > max) {
            max = s.size();
        }
    }
    return max;
}

// returns 0 if v is empty
int strUtil::minStringLength(const vector<string>& v) {
    int min = maxStringLength(v);
    for (const string& s : v) {
        if (s.size() < min) {
            min = s.size();
        }
    }
    return min;
}

string strUtil::removeLeadingCharacters(const string& s, char c) {
    int indexFirstNonCharacter = 0;
    for (int pos = 0; pos < s.size(); pos++) {
        if (s.at(pos) == c) {
            indexFirstNonCharacter++;
        } else {
            break;
        }
    }
    return s.substr(indexFirstNonCharacter);
}

string strUtil::removeLeadingSubstrings(const string& s, const string& sub) {
    int indexLastNonSubstring = 0;
    for (int pos = 0; pos < s.size(); pos += sub.size()) {
        if (isEqualAtPos(s, pos, sub)) {
            indexLastNonSubstring += sub.size();
        } else {
            break;
        }
    }
    return s.substr(indexLastNonSubstring);
}

string strUtil::removeTrailingCharacters(const string& s, char c) {
    int indexLastNonCharacter = s.size() - 1;
    for (int pos = s.size() - 1; pos >= 0; pos--) {
        if (s.at(pos) == c) {
            indexLastNonCharacter--;
        } else {
            break;
        }
    }
    return s.substr(0, indexLastNonCharacter + 1);
}

string strUtil::removeTrailingSubstrings(const string& s, const string& sub) {
    int indexLastNonSubstring = s.size() - sub.size();
    for (int pos = s.size() - sub.size(); pos >= 0; pos -= sub.size()) {
        if (isEqualAtPos(s, pos, sub)) {
            indexLastNonSubstring -= sub.size();
        } else {
            break;
        }
    }
    return s.substr(0, indexLastNonSubstring + sub.size());
}

string strUtil::removeLeadingSpaces(const string& s) {
    return removeLeadingCharacters(s, ' ');
}

string strUtil::removeTrailingSpaces(const string& s) {
    return removeTrailingCharacters(s, ' ');
}

string strUtil::trim(const string& s) {
    return removeLeadingSpaces(removeTrailingSpaces(s));
}

bool strUtil::containsIgnoreLeadingSpaces(const vector<string>& v, const string& s) {
    string sWithoutLeadingSpaces = removeLeadingSpaces(s);
    for (const string& e : v) {
        if (removeLeadingSpaces(e) == sWithoutLeadingSpaces) {
            return true;
        }
    }
    return false;
}

bool strUtil::containsIgnoreTrailingSpaces(const vector<string>& v, const string& s) {
    string sWithoutTrailingSpaces = removeTrailingSpaces(s);
    for (const string& e : v) {
        if (removeTrailingSpaces(e) == sWithoutTrailingSpaces) {
            return true;
        }
    }
    return false;
}

bool strUtil::containsTrimmed(const vector<string>& v, const string& s) {
    string sTrimmed = trim(s);
    for (const string& e : v) {
        if (trim(e) == sTrimmed) {
            return true;
        }
    }
    return false;
}

vector<string> strUtil::fillSpacesTo(const vector<string>& v, int size) {
    vector<string> filled = v;
    for (string& s : filled) {
        s += spaces(size - s.size());
    }
    return filled;
}

vector<string> strUtil::fillSpacesToMaxPlusN(const vector<string>& v, int n) {
    return fillSpacesTo(v, maxStringLength(v) + n);
}

string strUtil::quotify(const string& s) {
    return "\"" + s + "\"";
}

vector<string> strUtil::quotify(const vector<string>& v) {
    vector<string> quoted;
    for (const string& s : v) {
        quoted.push_back(strUtil::quotify(s));
    }
    return quoted;
}

vector<string> strUtil::spaceSplit(const string& s) {
    vector<string> v;
    string temp;
    for (char c : s) {
        if (c == ' ') {
            if (!temp.empty()) {
                v.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        v.push_back(temp);
    }
    return v;
}

string strUtil::toUpper(const string& s) {
    string n;
    for (char c : s) {
        n += (char) toupper(c);
    }
    return n;
}

string strUtil::toLower(const string& s) {
    string n;
    for (char c : s) {
        n += (char) tolower(c);
    }
    return n;
}

bool strUtil::equalsIgnoreCase(const string& s1, const string& s2) {
    return toUpper(s1) == toUpper(s2);
}

bool strUtil::isLetter(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool strUtil::isLowerCaseLetter(char c) {
    return 'a' <= c && c <= 'z';
}

bool strUtil::isUpperCaseLetter(char c) {
    return 'A' <= c && c <= 'Z';
}

bool strUtil::isDigit(char c) {
    return '0' <= c && c <= '9';
}

// separates a string into a list of words and spaces/punctuation, ex. "I am. Are you?" -> {"I", " ", "am", ". ", "Are", " ", "you", "?"}
vector<string> strUtil::separateIntoWordsAndSpaces(const string& s) {
    vector<string> parts;
    bool wordMode = true;
    string curr;
    for (char c : s) {
        if ((strUtil::isLetter(c) && wordMode) || (!strUtil::isLetter(c) && !wordMode)) {
            curr += c;
        } else {
            wordMode = !wordMode;
            parts.push_back(curr);
            curr = c;
        }
    }
    parts.push_back(curr);
    return parts;
}

vector<int> strUtil::getAsciiFromString(const string& s) {
    vector<int> points;
    for (char c : s) {
        points.push_back((std::uint8_t) c);
    }
    return points;
}

vector<char> strUtil::toCharVector(const string& s) {
    return vector<char>(s.begin(), s.end());
}

string strUtil::fromCharVector(const vector<char>& v) {
    return string(v.begin(), v.end());
}

vector<string> strUtil::split(const string& s, const string& delimiter) {
    vector<string> result;
    string curr;
    for (int i = 0; i < s.size();) {
        if (isEqualAtPos(s, i, delimiter)) {
            result.push_back(curr);
            curr.clear();
            i += delimiter.size();
        } else {
            curr += s.at(i);
            i++;
        }
    }
    result.push_back(curr);
    return result;
}

string strUtil::join(const vector<string>& v, const string& delimiter) {
    if (v.empty()) {
        return "";
    }
    string result = v.front();
    for (int i = 1; i < v.size(); i++) {
        result += delimiter + v.at(i);
    }
    return result;
}