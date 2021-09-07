/***********************************************|
|_________INFORMATION_ABOUT_THE_PROGRAM_________|
|    DEVELOPER: Поплавский Эльдар Эдуардович    |
|		  DATE: 27.04.2021                      |
|  DESCRIPTION: Программа читает из файла       |
|				все  множества. Формирует       |
|				множество  равное объединению   |
|				произвольного количества        |
|				исходных множеств (без учёта    |
|				кратных вхождений элементов).   |
|				Результат выводится  в  файл.   |
************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <regex>
 
using std::vector;
using std::string;
using std::regex;
using std::cin;
using std::cout;


/* User set. A set with a subsets. */
struct uset {
	vector <string> simple; // {}   || {a, b, <c, d>} 
	vector <uset> sets;     // {{}} || {a, {<b, {c, d}>, e}}
};


bool uset_check_input(string uset_string);
uset user_set_parse(string user_set_string, uset user_set);
void user_set_print(uset user_set);
uset unification(vector<uset> user_sets);
bool operator == (uset a, uset b);


int main(int argc, char* argv[])
{
	if (argv[1] != NULL) {
		cout << argv[1];
		freopen(argv[1], "r", stdin);
	}
	else 
		freopen("input.txt", "r", stdin);
	freopen("lab.log", "w", stdout);

	vector <uset> user_sets;
	vector <string> user_set_names;
	string full_user_set;  // Not processed entered users set

	/* Processing and saving all the entered sets */
	while (getline(cin, full_user_set)) {
		try {
			cout << "INPUT: " << full_user_set << "\n";
			// Checking the entered string for correctness
			if (!uset_check_input(full_user_set))
				throw(string("[INPUT ERROR]\n"));

			// Get name and body of current set [NAME->(E)=({...})<-BODY]
			int name_j = 0;
			string user_set_name;
			while (full_user_set[name_j] != '=') {
				user_set_name += full_user_set[name_j];
				name_j++;
			}
			name_j++;
			
			string user_set_string;
			for (int i = name_j + 1; i < full_user_set.size() - 1; i++)
				user_set_string += full_user_set[i];

			// Parsing and processing of the resulting set body
			uset user_set = user_set_parse(user_set_string, user_set);
			
			// Save of the processed set [uset]
			user_sets.push_back(user_set);
			user_set_names.push_back(user_set_name);

			// Output of the processed set
			cout << "RECOGNISED: " << user_set_name << "=";
			user_set_print(user_set);
			cout << "\n";
		}
		catch (string e) {
			cout << e;
		}
	}

	uset unificated_set = unification(user_sets);
	freopen("output.txt", "w", stdout);
	user_set_print(unificated_set);
}

/* Checking the correctness of the input */
bool uset_check_input(string user_set_string) {
	
	/* Check sets name && body [+ only allowed characters] */
	regex regular("([\\w]*\\=\\{)([\\w\\<\\>\\{\\},]*)");
	if (!(regex_match(user_set_string.c_str(), regular))) {
		cout << "Impossible to recognize the set ";
		return false;
	}

	// Get sets body to process it
	string user_set_body;
	int start = user_set_string.size(); // Start of sets body
	for (int i = 0; i < user_set_string.size() - 1; i++) {
		if (i > start)
			user_set_body += user_set_string[i];
		if (user_set_string[i] == '=')
			start = i + 1; // Immediately remove the symbol '{'
	}
	int length = user_set_body.size();

	/* Check brackets order and commas between them */
	int open_figure_brackets = 0, close_figure_brackets = 0;
	int open_simple_brackets = 0, close_simple_brackets = 0;
	int commas_between_simple_brackets = 0;

	vector <int> last_open_bracket_type; // [0 = '{'] && [1 = '<']
	last_open_bracket_type.push_back(0); // Every set first symbol is '{' 
	
	for (int j = 0; j < length; j++) {

		if (user_set_body[j] == '{') {
			open_figure_brackets++; 
			last_open_bracket_type.push_back(0);
		}
		if (user_set_body[j] == '}') {
			close_figure_brackets++;; 
			last_open_bracket_type.pop_back();
		}
		if (user_set_body[j] == '<') {
			open_simple_brackets++; 
			last_open_bracket_type.push_back(1);
		}
		
		if (user_set_body[j] == '>') { 
			
			close_simple_brackets++; 
			last_open_bracket_type.pop_back();

			if (open_simple_brackets == close_simple_brackets && open_simple_brackets != 0) {
				// Check all tuples have only 2 elements 
				// Count of '<' must be the same as count of ',' in tuples
				if (open_simple_brackets != commas_between_simple_brackets) {
					open_simple_brackets++;
					break;
				}
				else {
					open_simple_brackets = 0; 
					close_simple_brackets = 0;
					commas_between_simple_brackets = 0;
				}
			}
		}

		if (open_figure_brackets < close_figure_brackets || 
			open_simple_brackets < close_simple_brackets)
			break;

		/* Check commas between brackets in tuple */
		if (user_set_body[j] == ',' && last_open_bracket_type[last_open_bracket_type.size() - 1] == 1)
			if (open_simple_brackets > close_simple_brackets)
				commas_between_simple_brackets++;

		/**************************************************|
		|_________________CORRECT EXAMPLES_________________|
		| e={{},{}}										   |
		| E={0,{q},<a,d>,{{c,f},a}}						   |
		| W={0,{q},<a,d>,{<c,e>,a}}						   |
		| o={{},<<a,b>,<c,d>>}							   |
		| R={A,{},<{},{1,<1,<2,<3,4>>>}>,<{},{}>}          |
		| S={<{},{1,2}>}                                   |
		| N={<{},<{},<{<{},{}>,<{},{}>},<{},{<{},{}>}>>>>} |
		| P={<{<{},{}>},{}>}							   |
		|												   |
		|________________INCORRECT EXAMPLES________________|
		| g={{{},<{}>},<<a,b>,c>}						   |
		| i={<a>}  										   |
		| k={<{<{},<{},{}>>}{<{{},{}},{}>}>,<{},{}>,{}}    |
		|												   |
		***************************************************/
	}

	if (open_figure_brackets != close_figure_brackets ||
		open_simple_brackets != close_simple_brackets) {
		cout << "Incorrect brackets order ";
		return false;
	}

	/* Check symbols order in string */
	for (int i = 1; i < length - 1; i++) {
		// Check symbols near commas
		if (user_set_body[i] == ',' &&
		   (user_set_body[i - 1] == ',' || user_set_body[i + 1] == ',' ||
			user_set_body[i - 1] == '<' || user_set_body[i + 1] == '>' ||
			user_set_body[i - 1] == '{' || user_set_body[i + 1] == '}')) 
		{
			cout << "Incorrect commas ";
			return false;
		}
		// Check symbols near brackets
		if ((user_set_body[i] == '<' || user_set_body[i] == '{') && (
			(user_set_body[i - 1] != ',' && user_set_body[i - 1] != '<' &&  user_set_body[i - 1] != '{')))
		{
			cout << "Incorrect open brackets ";
			return false;
		}
		if ((user_set_body[i] == '>' || user_set_body[i] == '}') && (
			(user_set_body[i + 1] != ',' && user_set_body[i + 1] != '>' &&  user_set_body[i + 1] != '}')))
		{
			cout << "Incorrect close brackets ";
			return false;
		}
	}

	// First and last symbols in set can't be ',' 
	if (user_set_body.size() > 0 && (user_set_body[0] == ',' || user_set_body[length - 1] == ',')) {
		cout << "Incorrect commas ";
		return false;
	}

	return true;
}

/* Converting the passed string to a uset type */
uset user_set_parse(string user_set_string, uset user_set) {

	/* Check ne or more items received. [ {...} || {...} {...} ] */
	int open_figure_brackets = 0, close_figure_brackets = 0;
	for (int j = 0; j < user_set_string.size(); j++) {
		
		if (user_set_string[j] == '{') open_figure_brackets++;
		if (user_set_string[j] == '}') close_figure_brackets++;
	}

	/* If parser got set element [{...}] */
	if (user_set_string[0] == '{' && user_set_string[user_set_string.size() - 1] == '}' && (open_figure_brackets % 2 != 0)) {
		
		// Get set's body withot figure brackets
		uset user_set_child;
		string user_set_child_string;
		for (int i = 1; i < user_set_string.size() - 1; i++)
			user_set_child_string += user_set_string[i];

		// Parse it like simple uset
		user_set_child = user_set_parse(user_set_child_string, user_set_child);

		// Put uset at the end of uset's usets elements
		user_set.sets.push_back(user_set_child);
	}

	/* If parser got several elements or simple element [{...},a,b] */
	else {
		int child_begin = 0;
		for (int i = 0; i < user_set_string.size(); i++) {
			if (user_set_string[i] == ',' || i == user_set_string.size() - 1) {

				// Check and parse element(s)
				string child;
				
				/* If current element is set */
				if (user_set_string[child_begin] == '{') {
					int open_brackets = 0, close_brackets = 0, j = child_begin;
					do {
						if (user_set_string[j] == '{')
							open_brackets++;
						if (user_set_string[j] == '}')
							close_brackets++;
						j++;
					} while (open_brackets != close_brackets);

					// If it is not empty set [{a,b}]
					if (j - child_begin > 2) {
						for (int k = child_begin + 1; k < j - 1; k++)
							child += user_set_string[k];

						uset user_set_child;
						// Parse it and add to usets list in current uset
						user_set_child = user_set_parse(child, user_set_child);

						user_set.sets.push_back(user_set_child);
					}
					// If it is empty set [{}]
					else {
						child = string("{}");
						user_set.simple.push_back(string("{}"));
					}

					child_begin = j + 1; // Begin of next element
					i = j; // Skip current element symbols
				}
				/* If current element is tuple */
				else if (user_set_string[child_begin] == '<') {
					// Chech brackets
					int open_brackets = 0, close_brackets = 0, j = child_begin;
					do {
						if (user_set_string[j] == '<')
							open_brackets++;
						if (user_set_string[j] == '>')
							close_brackets++;
						j++;
					} while (open_brackets != close_brackets);

					// Perceived as a simple element
					for (int k = child_begin; k < j; k++)
						child += user_set_string[k];

					user_set.simple.push_back(child);

					child_begin = j + 1;
					i = j;
				}
				/* If current element is simple */
				else {
					// Put string at the end of uset's simple elements
					int j = child_begin;
					do {
						child += user_set_string[j];
						j++;
					} while (user_set_string[j] != ',' && j < user_set_string.size());

					user_set.simple.push_back(child);
					child_begin = i + 1;
				}
			}
		}
	}

	return user_set;
}

/* Output of all uset's elements */
void user_set_print(uset user_set) {
	cout << "{";
	// Output of simple elements
	for (int i = 0; i < user_set.simple.size(); i++) {
		cout << user_set.simple[i];
		if (i != user_set.simple.size() - 1 || user_set.sets.size() != 0)
			cout << ",";
		if (i == user_set.simple.size() - 1)
			cout << "";
	}
	
	// Output for simple elements of usets in uset 
	for (int i = 0; i < user_set.sets.size(); i++) {
		if (i != 0)
			cout << ",";
		user_set_print(user_set.sets[i]);
	}
	cout << "}";
}

/* Unification an arbitrary number of source sets */
uset unification(vector<uset> user_sets) {
	
	uset unificated_set;
	
	/* Get unique elemets from all usets and put them in one*/
	for (int i = 0; i < user_sets.size(); i++)
	{
		// For every uset in list we take all simple elements
		for (int j = 0; j < user_sets[i].simple.size(); j++) {
			
			// Check if it is already in the new uset
			bool element_was = false;
			for (int k = 0; k < unificated_set.simple.size(); k++) {
				if (user_sets[i].simple[j] == unificated_set.simple[k]) {
					element_was = true;
				}
			}
			if (!element_was) // If not, push it in back
				unificated_set.simple.push_back(user_sets[i].simple[j]);
		}

		// For every uset in list we take all uset elements [simple the same]
		for (int j = 0; j < user_sets[i].sets.size(); j++) {

			bool element_was = false;
			for (int k = 0; k < unificated_set.sets.size(); k++) {
				if (user_sets[i].sets[j] == unificated_set.sets[k]) {
					element_was = true;
				}
			}
			if (!element_was)
				unificated_set.sets.push_back(user_sets[i].sets[j]);
		}
	}

	return unificated_set;
}

/* Compare two usets */
bool operator == (uset a, uset b) {

	// Sets cannot be the same if their lengths are different
	if (a.sets.size() != b.sets.size() || a.simple.size() != b.simple.size())
		return false;
	
	/* Checking the identity of simple elements in usets */
	sort(a.simple.begin(), a.simple.end());
	sort(b.simple.begin(), b.simple.end());
	
	for (int i = 0; i < a.simple.size(); i++) {
		if (a.simple[i] != b.simple[i]) {
			return false;
		}
	}

	/* Checking the identity of usets as elements */
	uset c;
	for (int i = 0; i < a.sets.size(); i++) {
		for (int j = 0; j < b.sets.size(); j++) {
			if (a.sets[i] == b.sets[j]) { // Compare subsets
				c.sets.push_back(a.sets[i]);
				break;
			}
		}
	}

	// Sets cannot be the same if their lengths are different
	if (c.sets.size() != a.sets.size() && c.sets.size() != b.sets.size())
		return false;

	return true;
}