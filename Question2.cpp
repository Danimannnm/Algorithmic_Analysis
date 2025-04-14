#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <tuple>

class WildcardPatternMatcher {
private:
    std::vector<std::string> patterns;
    std::unordered_set<char> alphabet;
    std::unordered_map<int, std::unordered_map<char, int>> transitions;
    std::unordered_map<int, std::pair<int, std::string>> patternEndStates;

    void buildAlphabet() {
        // Build the alphabet set from all characters in the patterns (excluding wildcards)
        for (const std::string& pattern : patterns) {
            for (char c : pattern) {
                if (c != '?') {
                    alphabet.insert(c);
                    // Add uppercase and lowercase versions for case-insensitive matching
                    if (std::isalpha(c)) {
                        alphabet.insert(std::tolower(c));
                        alphabet.insert(std::toupper(c));
                    }
                }
            }
        }
    }

    void buildAutomaton() {
        // Build a combined finite automaton for all patterns with wildcard support
        int stateCounter = 0;

        // Process each pattern
        for (int patternIdx = 0; patternIdx < patterns.size(); ++patternIdx) {
            const std::string& pattern = patterns[patternIdx];
            int patternLength = pattern.length();
            
            // Get the start state for this pattern
            int patternStartState = stateCounter;
            
            // Build states for this pattern
            for (int i = 0; i <= patternLength; ++i) {
                int state = stateCounter + i;
                
                // For each state and each character in the alphabet
                for (char c : alphabet) {
                    // Calculate the next state
                    int nextState;
                    
                    if (i < patternLength && (pattern[i] == c || pattern[i] == '?')) {
                        nextState = state + 1;
                    } else {
                        // Try to find the longest proper suffix that is also a prefix
                        int k = std::min(i, patternLength);
                        while (k > 0) {
                            // Check if the suffix matches the prefix considering wildcards
                            bool isMatch = true;
                            for (int j = 0; j < k; ++j) {
                                if (j < i && pattern[j] != '?' && pattern[j] != pattern[i-k+j]) {
                                    isMatch = false;
                                    break;
                                }
                            }
                            
                            if (isMatch) {
                                break;
                            }
                            --k;
                        }
                        
                        nextState = patternStartState + k;
                    }
                    
                    // Add transition
                    transitions[state][c] = nextState;
                }
            }
            
            // Mark the final state for this pattern
            patternEndStates[stateCounter + patternLength] = {patternIdx, pattern};
            
            // Update state counter for the next pattern
            stateCounter += patternLength + 1;
        }
    }

public:
    WildcardPatternMatcher(const std::vector<std::string>& patternList) : patterns(patternList) {
        buildAlphabet();
        buildAutomaton();
    }

    std::vector<std::tuple<int, std::string, int>> search(const std::string& text) {
        // Search for all patterns in the given text
        std::vector<std::tuple<int, std::string, int>> results;
        int currentState = 0;
        
        for (int i = 0; i < text.length(); ++i) {
            char c = text[i];
            
            // Skip character if not in alphabet (could be punctuation, space, etc.)
            if (alphabet.find(c) != alphabet.end()) {
                // Transition to the next state
                if (transitions.find(currentState) != transitions.end() && transitions[currentState].find(c) != transitions[currentState].end()) {
                    currentState = transitions[currentState][c];
                } else {
                    currentState = 0;  // Reset to initial state
                }
            } else {
                currentState = 0;  // Reset for characters not in alphabet
            }
            
            // Check if we've reached an accept state
            if (patternEndStates.find(currentState) != patternEndStates.end()) {
                int patternIdx = patternEndStates[currentState].first;
                const std::string& pattern = patternEndStates[currentState].second;
                int patternLength = pattern.length();
                
                // Extract the actual matched substring
                int startPos = i - patternLength + 1;
                std::string actualMatch = text.substr(startPos, patternLength);
                
                // Verify the match considering wildcards
                bool matches = true;
                for (int j = 0; j < patternLength; ++j) {
                    if (j < pattern.length() && pattern[j] != '?' && 
                        std::tolower(pattern[j]) != std::tolower(actualMatch[j])) {
                        matches = false;
                        break;
                    }
                }
                
                if (matches) {
                    results.push_back(std::make_tuple(patternIdx, actualMatch, startPos));
                }
            }
        }
        
        return results;
    }
};

// Process the input file according to the specified format
std::pair<std::vector<std::string>, std::vector<std::string>> processInput(const std::string& input) {
    std::vector<std::string> patterns;
    std::vector<std::string> textLines;
    std::istringstream iss(input);
    std::string line;
    
    // Parse number of patterns
    int numPatterns;
    std::getline(iss, line);
    numPatterns = std::stoi(line);
    
    // Parse patterns
    for (int i = 0; i < numPatterns; ++i) {
        std::getline(iss, line);
        patterns.push_back(line);
    }
    
    // Parse number of text lines
    int numLines;
    std::getline(iss, line);
    numLines = std::stoi(line);
    
    // Parse text lines
    for (int i = 0; i < numLines; ++i) {
        std::getline(iss, line);
        textLines.push_back(line);
    }
    
    return {patterns, textLines};
}

// Format the search results according to the specified output format
std::string formatOutput(const std::vector<std::vector<std::tuple<int, std::string, int>>>& results,
                         const std::vector<std::string>& patterns,
                         const std::vector<std::string>& textLines) {
    std::ostringstream output;
    
    for (int i = 0; i < results.size(); ++i) {
        output << "Matches in Line " << (i + 1) << ":\n";
        
        if (results[i].empty()) {
            output << "No match found\n";
        } else {
            // Create a copy for sorting
            std::vector<std::tuple<int, std::string, int>> sortedResults = results[i];
            // Sort results by position
            std::sort(sortedResults.begin(), sortedResults.end(), 
                     [](const auto& a, const auto& b) {
                         return std::get<2>(a) < std::get<2>(b);
                     });
            
            for (const auto& result : sortedResults) {
                int patternIdx = std::get<0>(result);
                const std::string& actualMatch = std::get<1>(result);
                int position = std::get<2>(result);
                
                output << patterns[patternIdx] << ": " << actualMatch << " at index " << position << "\n";
            }
        }
    }
    
    return output.str();
}

int main() {
    // For demonstration, use the example from the problem
    std::string exampleInput = "3\n"
                              "a?ple\n"
                              "banana\n"
                              "g?ape\n"
                              "2\n"
                              "I love eating an Apple and a Banana.\n"
                              "Grapes are my favorite fruit, but I also like banana and apple.";
    
    auto [patterns, textLines] = processInput(exampleInput);
    
    // Create the pattern matcher
    WildcardPatternMatcher matcher(patterns);
    
    // Search for patterns in each text line
    std::vector<std::vector<std::tuple<int, std::string, int>>> allResults;
    for (const std::string& text : textLines) {
        allResults.push_back(matcher.search(text));
    }
    
    // Format and print the output
    std::string output = formatOutput(allResults, patterns, textLines);
    std::cout << output;
    
    return 0;
}