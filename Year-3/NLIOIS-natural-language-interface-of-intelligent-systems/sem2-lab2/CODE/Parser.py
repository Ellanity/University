import spacy
from spacy import displacy


class Parser:

    def __init__(self):
        self.subordination_trees = []
        self.components_system = []

    def syntacic_analysis_subordination_trees(self):
        """
        Синтаксический разбор с помощью деревьев разбора
        :return:
        """
        nlp = spacy.load('ru_core_news_sm')
        # doc = nlp(self.text)
        doc = nlp('Это может оказаться единственным выходом.')

        # попробовала подобрать эти наборы букв под что-то более менее подходящее
        for token in doc:
            if token.dep_ == 'nsubj' or token.dep_ == 'nsubj:pass' or token.dep_ == 'csubj' or token.dep_ == 'xcomp':
                print(token.text, token.pos_, 'подлежащее')
                self.subordination_trees.append('подлежащее')
            elif token.dep_ == 'ROOT' or token.dep_ == 'conj' or token.dep_ == 'expl' or token.dep_ == 'parataxis' or token.dep_ == 'aux' or token.dep_ == 'ccomp':
                print(token.text, token.pos_, 'глагол')
                self.subordination_trees.append('глагол')
            elif token.dep_ == 'advmod' or token.dep_ == 'discourse' or token.dep_ == 'advcl':
                print(token.text, token.pos_, 'обстоятельство')
                self.subordination_trees.append('обстоятельство')
            elif token.dep_ == 'obj' or token.dep_ == 'nummod' or token.dep_ == 'obl' or token.dep_ == 'iobj':
                print(token.text, token.pos_, 'дополнение')
                self.subordination_trees.append('дополнение')
            elif token.dep_ == 'nmod' or token.dep_ == 'amod' or token.dep_ == 'det' or token.dep_ == 'acl':
                print(token.text, token.pos_, 'определение')
                self.subordination_trees.append('определение')
            elif token.dep_ == 'cc' or token.dep_ == 'fixed' or token.dep_ == 'mark':
                print(token.text, token.pos_, 'союз')
                self.subordination_trees.append('союз')
            elif token.dep_ == 'case':
                print(token.text, token.pos_, 'предлог')
                self.subordination_trees.append('предлог')
            else:
                print(token.text, token.pos_, token.dep_)
                self.subordination_trees.append(token.dep_)

    def syntacic_analysis_component_systems(self, text):
        nlp = spacy.load('ru_core_news_sm')
        doc = nlp(text)

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

                if token.dep_ == 'punct':
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
                elif token.dep_ == 'nmod' or token.dep_ == 'amod' or token.dep_ == 'det' or token.dep_ == 'acl':
                    analysis_sentence += '(' + token.text + ' '
                    left_bracket += 1
                elif token.dep_ == 'case':
                    analysis_sentence += '(' + token.text + ' ' + '('
                    left_bracket += 2
                else:
                    analysis_sentence += token.text + ' '
            if left_bracket != right_bracket:
                for i in range(left_bracket - right_bracket):
                    analysis_sentence += ')'
            analysis_sentence += '.'
            self.components_system.append(analysis_sentence)
            print(analysis_sentence)
