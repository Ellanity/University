import csv


class WordForm:
    def __init__(self, form, pos, gender, number, case, frequency):
        self.form = form
        self.pos = pos
        self.gender = gender
        self.number = number
        self.case = case
        self.frequency = frequency


class WordForms:
    def __init__(self):
        self.forms = {}
        self.tags = {}
        self.sorted_forms = []

    def add(self, form, pos, gender, number, case):
        if form not in self.forms:
            self.forms[form] = 0
            self.tags[form] = WordForm(form, pos, gender, number, case, 0)
        self.forms[form] += 1
        self.tags[form].frequency += 1

    def delete(self, form):
        self.forms.pop(form, None)
        self.tags.pop(form, None)

    def update(self, form, pos, gender, number, case, count):
        if form not in self.forms:
            self.add(form, pos, gender, number, case)
        else:
            self.tags[form].pos = pos
            self.tags[form].gender = gender
            self.tags[form].number = number
            self.tags[form].case = case
            self.tags[form].frequency = count
            self.forms[form] = count

    def sort(self):
        self.sorted_forms = sorted(self.forms, key=str.lower)

    def clear(self):
        self.forms = {}
        self.tags = {}
        self.sorted_forms = []

    def save(self, filename):
        with open(filename, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile, dialect="excel")
            writer.writerow(['Form', 'POS', 'Gender', 'Number', 'Case', 'Frequency'])

            if hasattr(self, 'sorted_forms'):
                for form in self.sorted_forms:
                    tag = self.tags[form]
                    writer.writerow([form, tag.pos, tag.gender, tag.number, tag.case, tag.frequency])
            else:
                for form, tag in self.tags.items():
                    writer.writerow([form, tag.pos, tag.gender, tag.number, tag.case, tag.frequency])
