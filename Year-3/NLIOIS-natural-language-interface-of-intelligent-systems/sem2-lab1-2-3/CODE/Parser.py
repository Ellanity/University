import spacy
from nltk import WordNetLemmatizer, pos_tag
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
from nltk.stem.snowball import RussianStemmer
from nltk.stem import WordNetLemmatizer
from nltk import pos_tag
import spacy
import pymorphy2
from nltk.corpus import wordnet as wn
from pattern.en import pluralize, singularize, conjugate


class Parser:
    def __init__(self):
        # ### all needed lists ### #
        # parse text
        self.subordination_trees_filled = []
        self.components_system = []
        # parse words
        self.morph = pymorphy2.MorphAnalyzer()
        self.stemmer = RussianStemmer()

        self.__re_init_lists_()

    def __re_init_lists_(self):
        self.normal_form_lists = []
        self.semantic_analysis_list_of_dicts = []
        self.words_dict = {}
        self.word_list = []
        self.filtered_list = []
        self.normal_form_dict = {}
        self.word_info_list = []
        self.word_base_list = set()
        self.word_ending_dict = {}
        self.stop_words = []

    # ### Parse text ### #
    def syntax_analysis_subordination_trees(self, sentence):
        """Parsing using parse trees :return:"""
        nlp = spacy.load("en_core_web_sm")
        doc = nlp(sentence)

        # I tried to pick up these sets of letters for something more or less suitable
        for token in doc:
            if token.dep_ == "nsubj" or token.dep_ == "nsubj:pass" or token.dep_ == "csubj" or token.dep_ == "xcomp":
                # print(token.text, token.pos_, 'subject')
                # self.subordination_trees.append("subject")
                self.subordination_trees_filled.append([token.text, token.pos_, "subject"])
            elif token.dep_ == "ROOT" or token.dep_ == "conj" or token.dep_ == "expl" or token.dep_ == "parataxis" or token.dep_ == "aux" or token.dep_ == "ccomp":
                # print(token.text, token.pos_, 'verb')
                # self.subordination_trees.append('verb')
                self.subordination_trees_filled.append([token.text, token.pos_, "verb"])
            elif token.dep_ == "advmod" or token.dep_ == "discourse" or token.dep_ == "advcl":
                # print(token.text, token.pos_, 'circumstance')
                # self.subordination_trees.append('circumstance')
                self.subordination_trees_filled.append([token.text, token.pos_, "circumstance"])
            elif token.dep_ == "obj" or token.dep_ == "nummod" or token.dep_ == "obl" or token.dep_ == "iobj":
                # print(token.text, token.pos_, 'addition')
                # self.subordination_trees.append('addition')
                self.subordination_trees_filled.append([token.text, token.pos_, "addition"])
            elif token.dep_ == "nmod" or token.dep_ == "amod" or token.dep_ == "det" or token.dep_ == "acl":
                # print(token.text, token.pos_, 'definition')
                # self.subordination_trees.append('definition')
                self.subordination_trees_filled.append([token.text, token.pos_, "definition"])
            elif token.dep_ == "cc" or token.dep_ == "fixed" or token.dep_ == "mark":
                # print(token.text, token.pos_, 'union')
                # self.subordination_trees.append('union')
                self.subordination_trees_filled.append([token.text, token.pos_, "union"])
            elif token.dep_ == "case":
                # print(token.text, token.pos_, 'preposition')
                # self.subordination_trees.append('preposition')
                self.subordination_trees_filled.append([token.text, token.pos_, "preposition"])
            else:
                # print(token.text, token.pos_, token.dep_)
                # self.subordination_trees.append(token.dep_)
                self.subordination_trees_filled.append([token.text, token.dep_, "undefined"])

    def syntax_analysis_component_systems(self, sentence):
        nlp = spacy.load("en_core_web_sm")
        doc = nlp(sentence)

        # take each sentence
        for sentence in doc.sents:
            analysis_sentence = '('
            left_bracket, right_bracket = 1, 0
            for token in sentence:
                # if token.dep_ == 'cc' or token.dep_ == 'fixed' or token.dep_ == 'mark':
                #     pass
                # if left_bracket:
                #     left_bracket = False
                #     l += f'{token.text})'
                # elif not left_bracket:
                #     left_bracket = True
                #     l += f'({token.text}'

                if token.dep_ == "punct":
                    if token.text != '.':
                        if left_bracket != right_bracket:
                            for i in range(left_bracket - right_bracket - 1):
                                analysis_sentence += ')'
                            right_bracket = left_bracket - 1
                            analysis_sentence += token.text + ' ' + '('
                            right_bracket += 1
                            left_bracket += 1
                        elif left_bracket == right_bracket:
                            analysis_sentence += token.text + ' ' + '('
                            left_bracket += 1
                elif token.dep_ == "nmod" or token.dep_ == "amod" or token.dep_ == "det" or token.dep_ == "acl":
                    analysis_sentence += '(' + token.text + ' '
                    left_bracket += 1
                elif token.dep_ == "case":
                    analysis_sentence += '(' + token.text + ' ' + '('
                    left_bracket += 2
                else:
                    analysis_sentence += token.text + ' '
            if left_bracket != right_bracket:
                for i in range(left_bracket - right_bracket):
                    analysis_sentence += ')'
            analysis_sentence += '.'
            self.components_system.append(analysis_sentence)
            return analysis_sentence
            # print(analysis_sentence)

    # ### Parse words ### #
    def prepare_text(self, text):
        """Function to make all nessesary text's manipulations"""
        # a list of all words is formed
        self.filter_text(text)
        # all lists and dictionaries with information by words are filled in
        self.get_word_info()
        # endings of words
        self.get_word_ending_list()
        # self.preprocess()

    def get_word_ending_list(self):
        # print(self.word_list)
        for word in self.words_dict:
            # print('# ',self.stemmer.stem(word))
            buf_list = []
            # print(self.morph.parse(word)[0].inflect({'gent'}))
            for i in self.morph.parse(word)[0].lexeme:
                # print('= ', i.word)
                if self.stemmer.stem(word) in i.word:
                    # print('- ', i.word.replace(self.stemmer.stem(word),''))
                    buf_list.append(i.word.replace(self.stemmer.stem(word), ''))
            self.word_ending_dict[self.stemmer.stem(self.morph.parse(word)[0].word)] = buf_list

    """
    def get_inflect_on_word_case(self, word, word_case, word_number):
        # Formation of word forms according to a given number and case
        try:
            if word_case == 'Nominative' and word_number == 'Singular':
                print(singularize(word))
            elif word_case == 'Nominative' and word_number == 'Plural':
                print(pluralize(word))
            elif word_case == 'Genitive' and word_number == 'Singular':
                # Perform appropriate inflection for genitive case in singular number
                # You can use a library like inflect or implement specific rules
                # Example using pattern.en:
                print(conjugate(word, tense="genitive"))
            elif word_case == 'Genitive' and word_number == 'Plural':
                # Perform appropriate inflection for genitive case in plural number
                # You can use a library like inflect or implement specific rules
                # Example using pattern.en:
                print(pluralize(word, pos='NNS'))
            elif word_case == 'Accusative' and word_number == 'Singular':
                # Perform appropriate inflection for accusative case in singular number
                # Example using pattern.en:
                print(conjugate(word, tense="accusative"))
            elif word_case == 'Accusative' and word_number == 'Plural':
                # Perform appropriate inflection for accusative case in plural number
                # Example using pattern.en:
                print(pluralize(word, pos='NNS', role='object'))
            elif word_case == 'Possessive' and word_number == 'Singular':
                # Perform appropriate inflection for possessive case in singular number
                # Example using pattern.en:
                print(conjugate(word, tense="possessive"))
            elif word_case == 'Possessive' and word_number == 'Plural':
                # Perform appropriate inflection for possessive case in plural number
                # Example using pattern.en:
                print(pluralize(word, pos='NNS', role='possessive'))
            elif word_case == 'Subjective' and word_number == 'Singular':
                # Perform appropriate inflection for subjective case in singular number
                # Example using pattern.en:
                print(conjugate(word, tense="infinitive"))
            elif word_case == 'Subjective' and word_number == 'Plural':
                # Perform appropriate inflection for subjective case in plural number
                # Example using pattern.en:
                print(pluralize(word, pos='NNS', role='subject'))
            elif word_case == 'Objective' and word_number == 'Singular':
                # Perform appropriate inflection for objective case in singular number
                # Example using pattern.en:
                print(conjugate(word, tense="3sg"))
            elif word_case == 'Objective' and word_number == 'Plural':
                # Perform appropriate inflection for objective case in plural number
                # Example using pattern.en:
                print(pluralize(word, pos='NNS', role='object'))
            # Add more cases and numbers as needed

        except Exception as _:
            pass
"""
    def get_word_info(self):
        lemmatizer = WordNetLemmatizer()
        for token in self.filtered_list:
            pos = pos_tag([token])[0][1]
            if pos not in ['PRP', 'NNP', 'CD', 'PRP$', 'DT', 'POS'] and '-' not in token:
                if token not in self.words_dict.keys():
                    word_info = pos_tag([token])[0]
                    self.words_dict[token] = word_info[1].split()
                    self.word_list.append(token)
                    self.normal_form_dict[token] = lemmatizer.lemmatize(token)
                    self.word_info_list.append(word_info[1].split())
                    self.word_base_list.add(lemmatizer.lemmatize(token))

    def show_info(self):
        print(len(self.words_dict), self.words_dict)
        print(len(self.normal_form_dict), self.normal_form_dict)
        print(len(self.word_info_list), self.word_info_list)
        print(len(self.word_base_list), self.word_base_list)
        print(len(self.word_ending_dict), self.word_ending_dict)

    def filter_text(self, text: str):
        """Generates an alphabetically sorted list of words"""
        # get rid of necessary words
        self.stop_words = set(stopwords.words("english"))
        for word in word_tokenize(text):
            if word.casefold() not in self.stop_words:
                self.filtered_list.append(word)

        # get rid of punctuation symbols
        filtered = list(filter(lambda x: x != ',' and x != '.' and x != ', ', self.filtered_list))
        self.filtered_list = list(filtered)

        # lowercase all the words and sort them
        self.filtered_list = sorted([x.lower() for x in self.filtered_list])

    def preprocess(self, text, stop_words, punctuation_marks, morph):
        # print('---', text)
        tokens = word_tokenize(text)
        preprocessed_text = []
        for token in tokens:
            if token.casefold() not in self.stop_words:
                lemma = morph.parse(token)[0].normal_form
                preprocessed_text.append(lemma)
            # if token not in punctuation_marks:
            #     lemma = morph.parse(token)[0].normal_form
            #     if lemma not in self.stop_words:
            #         preprocessed_text.append(lemma)
        return preprocessed_text

    def semantic_analysis(self):
        self.semantic_analysis_list_of_dicts = []
        # list(set(self.word_base_list))
        for word in self.word_base_list:
            synsets = wn.synsets(word)
            if len(synsets) != 0:
                dict = {}
                synonyms_list = []
                definition_dict = {}
                # definition = ""
                hypernyms_list = []
                hyponyms_list = []

                # synonym, definition
                for syn in synsets:
                    # for lemma in syn.lemmas():
                    if syn.lemmas()[0].name() not in synonyms_list:
                        synonyms_list.append(syn.lemmas()[0].name())
                    definition_dict[syn.lemmas()[0].name()] = syn.definition()
                    # print(definition_dict)
                # hypernyms
                for hypernym in synsets[0].hypernyms():
                    for lemma in hypernym.lemmas():
                        if lemma.name() not in hypernyms_list:
                            hypernyms_list.append(lemma.name())
                # hyponyms
                for hyponym in synsets[0].hyponyms():
                    for lemma in hyponym.lemmas():
                        if lemma.name() not in hyponyms_list:
                            hyponyms_list.append(lemma.name())
                # print(dict)
                # fill the result list
                dict['word'] = word
                dict['definitions'] = definition_dict
                dict['synonyms'] = synonyms_list
                dict['hypernyms'] = hypernyms_list
                dict['hyponyms'] = hyponyms_list
                self.semantic_analysis_list_of_dicts.append(dict)
                # print(dict)

    def parse_words(self, text):
        self.__re_init_lists_()
        # compiles all necessary dictionaries and lists for further work
        self.prepare_text(text)
        # adds all data about synonyms, etc. to the list of semantic_analysis_list_of_dicts
        self.semantic_analysis()
        import json
        in_json = json.dumps(self.semantic_analysis_list_of_dicts, ensure_ascii=False, indent=4)
        return in_json
