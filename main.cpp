#include <iostream>
#include "BinarySearchTree.hpp"
#include "csvstream.hpp"
#include "Map.hpp"
#include <cassert>  //assert
#include <utility>  //pair
#include <iostream>
#include <fstream>
using namespace std;

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier { 
    public:

        void training_function (csvstream& train_stream, bool debug) { 
            string row_tag = row["tag"];
            string row_content = row["content"];
            if (debug){ cout << "training data: " << endl;}
            while (train_stream >> row) {
                //updating total number of posts in training set
                number_of_total_posts++;
                if (debug) {
                    // switched to row["tag"] and ["content"]
                    cout << "label = " << row["tag"] << ", content = " 
                                << row["content"] << endl;
                }
                
                //updates label_map with key label and post number value
                if (label_map.find(row_tag) == label_map.end()) { 
                    label_map.insert({row_tag,1});
                } else { 
                    label_map[row_tag]++;
                }
        
                set<string> uw_set_per_row = unique_words(row_content);

                for (const string &current_word : uw_set_per_row) { 
                    //uwords_set is the one with no duplicates 
                    uwords_set.insert(current_word);
                    //works below will initialize everything at first
                    //and the increment as it comes across it
                    //updates word_map with key word and post number value
                    if (word_map.find(current_word) == word_map.end()) { 
                        word_map.insert({current_word, 1});
                    } else {
                        word_map[current_word]++;
                    }
                    //update lw_map of pairs
                    if (lw_map.find({row_tag, current_word}) == lw_map.end()) { 
                        lw_map.insert({{row_tag, current_word}, 1});
                    } else {
                    lw_map[{row_tag, current_word}]++;
                    }
                    
                     if (debug) { 
                        cout << "classifier parameters: " << endl;
                        cout << row["tag"] << ":" << current_word << " count = " 
                            << word_map[current_word] << ", log-likelihood = " << 
                            log_likelihood(row_tag, current_word) << endl;
                    }
                }
            number_of_uwords = uwords_set.size();
            }
           
            cout << "trained on " << number_of_total_posts << " examples" << endl
             << endl;
            if (debug) { 
                cout << "vocabulary size = " << number_of_uwords << endl << endl;
            }
            if (debug) { 
                    cout << "classes: " << endl; 
                    cout << row["tag"] << " , " << label_map[row_tag] 
                        << " examples, log-prior = " << log_prior(row["tag"]) << endl;
                }
            
        }

        //working with one label-- iterate through labels in log_prob
        double log_prior (string C) { //call in testing 
            return log(label_map[C]/number_of_total_posts);
        }

        //working with one word 
        double log_likelihood (string C, string w) { 
            if ((lw_map.find({C, w}) == lw_map.end()) && 
                                            (uwords_set.find(w) != uwords_set.end())) { 
                return log(word_map[w]/number_of_total_posts);
            }
            if (uwords_set.find(w) == uwords_set.end()) { 
                return log(1/number_of_total_posts);
            }
            return log(lw_map[{C, w}]/label_map[C]);
        }

        string log_prob (set <string> post) { 
            double ll = 0;
            double max_lprob;
            string final_label;
            for (const auto &labels : label_map)  { 
                double lp = log_prior(labels.first);
                //cout << "log prior " << lp << endl;
                for (const auto &words : post) { 

                    ll += log_likelihood(labels.first, words);
                     //cout << "log l = " << ll << endl;
                    
                }
                double lprob = lp + ll;
                if (lprob > max_lprob) { 
                    max_lprob = lprob; 
                    final_label = labels.first;
                } 
            }
            final_score = max_lprob;
            return final_label;
        }

double log_prob_score () { 
return final_score;
 }

        //testing function
        void testing_function(csvstream& test, bool debug){
            //going through every post and considering every poossible label from the 
            //training set that the test post could have
            // doing calculation of the probability 
            // calculatuion for every possible label
            cout << "test data: " << endl;
            map <string, string> row;
            int performance = 0;
            int total = 0;
            while (test >> row){
                string row_content = row["content"];
                string row_tag = row["tag"];
                set<string> individual_row = unique_words(row["content"]);
                string predicted = log_prob(individual_row);
                cout << "correct = " << row_tag << ", predicted = " << predicted 
                    << ", log-probability score = " << final_score << endl;
                cout << "content = " << row_content << endl << endl;
                total++; 

                if (row_tag == predicted) { 
                    performance++;
                }
            } 
            cout << "performance: " << performance << " / " << total 
                << " posts predicted correctly" << endl;
        }


    private:
        int number_of_total_posts = 0;
        int number_of_uwords;
        //For each word w, the number of posts in the training set that contain w
        Map <string,int> word_map; 
        //For each label C, the number of posts with that label 
        Map <string,int> label_map;
        //For each label C and word w, the number of posts with label C that contain w 
        Map<pair<string, string>, int> lw_map;

        double final_score; 

        map <string, string> row;
        set<string> uwords_set;
        set<string> labels_set;
};


int main(int argc, char** argv) { 
    cout.precision(3);
    //check command line arguments
    string train_file_name = argv[1];
    string test_file_name = argv[2];
    //make cvs streams using files 
    csvstream training(train_file_name);
    csvstream testing(test_file_name);
    bool debug_dec = false;

    if (argc < 3) { 
        cout << "Too few arguements" << endl;
    }

    if (argc == 4 && (strcmp(argv[3],"--debug") == 0)) { 
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        debug_dec = true;
    }

    if (!training) {
        cout << "Error opening file: " << train_file_name << endl;
        return 1;
    }

    if (!testing) {
        cout << "Error opening file: " << test_file_name << endl;
        return 1;
    }
    Classifier c; 
    c.training_function(training, debug_dec);
    c.testing_function(testing, debug_dec);
    return 0;
}

