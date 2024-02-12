#include <iostream>
#include<algorithm>
#include<list>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<array>

using namespace std;

const int VerticesMax = 20;
const int TransValue = 3;

string read_file_name();
vector<vector <string> > read_from_file(string file_name);
bool check_if_1graph(int vertex_count, int matrix[VerticesMax][VerticesMax]);
bool check_if_conjugated( int vertex_count,int matrix[VerticesMax][VerticesMax]) ;
bool check_if_linear(int vertex_count, int matrix[VerticesMax][VerticesMax]);
void transformation_of_matrix(int vertex_count, int matrix[VerticesMax][VerticesMax], string filename);
void print_results(string filename);

int main() 
{
    vector<vector<string>> main_vector; 

    string filename = read_file_name();
    main_vector = read_from_file(filename);

    int vertex_count = main_vector.size();
    int matrix[VerticesMax][VerticesMax] = { 0 };

    for (int i = 0; i < main_vector.size(); i++)
    {
        int first_vertex = stoi(main_vector[i][0]) - 1; 
        for (int j = 1; j < main_vector[i].size(); j++) 
        {
            int a = stoi(main_vector[i][j]) - 1;
            matrix[first_vertex][a] += 1;
        }
    }

	if (check_if_1graph(vertex_count, matrix)) { 
		if (check_if_conjugated(vertex_count, matrix)) {
			if (check_if_linear(vertex_count, matrix)) {
				cout << endl << "Graf jest sprzezony" << endl;
				cout << "Graf jest liniowy" << endl;
			}
			else
			{
				cout << endl << "Graf jest sprzezony" << endl;
				cout << "Graf nie jest liniowy" << endl;
			}
			transformation_of_matrix(vertex_count, matrix, filename);
		}
		else
		{
			cout << endl << "Graf nie jest sprzezony" << endl;
			cout << "Graf nie jest liniowy" << endl;
		}
	}
	else
	{
		cout << endl << "Graf nie jest sprzezony" << endl;
		cout << "Graf nie jest liniowy" << endl;
	}

return 0;
}

string read_file_name() {
    string filename;
    cout << "Podaj nazwe pliku z grafem: ";
    cin >> filename;
    filename += ".txt";
    return filename;
}

vector<vector<string> > read_from_file(string filename) {
    vector<string> consequents = {};
    vector<vector<string>> main_vector = {};
    ifstream graphIN;
    graphIN.open(filename, ios::out);
    if (graphIN.is_open())
    {
        string line;
        string element;
        while (getline(graphIN, line))
        {
            for_each(begin(line), end(line), [&](char const ch)
                {
                    if (ch != ' ')
                    {
                        element += ch;
                    }
                    else
                    {
                        if (element.length() > 0) {
                            consequents.push_back(element);
                            element.clear();
                        }
                    }
                });

            if (element.length() > 0)
            {
                consequents.push_back(element);
                element.clear();
            }
            main_vector.push_back(consequents);
            consequents.clear();
        }
        graphIN.close();
        return main_vector;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku. Sprobuj jeszcze raz." << endl;
        exit(0);
    }
}

bool check_if_1graph(int vertex_count, int matrix[VerticesMax][VerticesMax]) 
{
    for (int i = 0; i < vertex_count; i++) 
    {
        for (int j = 0; j < vertex_count; j++) 
        {
            if (matrix[i][j] != 0 && matrix[i][j] != 1) 
            {
                return false;
            }
        }
    }
    return true;
}

bool check_if_conjugated(int vertex_count , int matrix[VerticesMax][VerticesMax]){
    for(int x = 0; x < vertex_count-1;x++) { 
        for (int i = 1 + x; i < vertex_count - x; i++) {
            bool match = false;
            bool mismatch = false;
            for (int j = 0; j < vertex_count; j++) {
                if (matrix[x][j] != matrix[i][j] && (matrix[x][j] == 1 || matrix[i][j] == 1)) {
                    mismatch = true;
                }
                else if(matrix[x][j] == matrix[i][j] && matrix[x][j] == 1){
                    match = true;
                }
            }
            if(match == mismatch){
                return false;
            }
        }
    }
    return true;
}

bool check_if_linear(int vertex_count, int matrix[VerticesMax][VerticesMax]){
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            for (int x = 0; x < vertex_count; x++) {

                if (matrix[i][j] == matrix[i][x] == 1) {
                    for (int y = 0; y < vertex_count; y++) {
                        if (matrix[j][y] == matrix[x][y] == 1) {
                            return false;
                        }
                    }
                }
                if (matrix[i][i] == 1) {
                    if ((matrix[i][j] == matrix[j][i] == 1) && (matrix[j][j] == 1)) {
                        return false;
                    }
                }
            }
        }

    }
    return true;
}

void transformation_of_matrix(const int vertex_count, int matrix[VerticesMax][VerticesMax], string filename) {
    int counter = 1;
    int tab_input = 0;

    vector<array<int, TransValue> > tab(vertex_count);

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < TransValue; j++) {
            tab[i][j] = 0;
        }
    }

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 1; j < TransValue; j++) {
            tab[i][j] = counter++;
        }
    }

    tab_input = 0;
    for (int i = 0; i < vertex_count; i++) {

        for (int k = 0; k < vertex_count; k++) {
            if (matrix[k][i] == 1) {
                tab[i][0] = i + 1;
                tab[k][2] = tab[i][1];
            }
        }
        for (int y = 0; y < vertex_count; y++) {
            if (matrix[i][y] == 1) {
                tab[i][0] = i + 1;
                tab[y][1] = tab[i][2];
            }
        }

    }

    cout << endl << "transformed vertex to links" << endl;
    for (int i = 0; i < vertex_count; i++)
    {
        cout << tab[i][0] << "\t" << tab[i][1] << " -> " << tab[i][2] << endl;
    }

    vector<array<int, 2> > tab_homogenesis(vertex_count);
    int minify_vertices = 0;
    int helper_variable;

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < 2; j++) {
            tab_homogenesis[i][j] = tab[i][j + 1];
            tab_homogenesis[i][j] += 50;
        }
    }
    cout << endl;
    for (int i = 0; i < vertex_count; i++) { 
        for (int j = 0; j < 2; j++) { 
            if (tab_homogenesis[i][j] > minify_vertices) {
                helper_variable = tab_homogenesis[i][j]; 
                minify_vertices++;
                for (int x = 0; x < vertex_count; x++) { 
                    for (int y = 0; y < 2; y++) {
                        if (tab_homogenesis[x][y] ==
                            helper_variable) { 
                            tab_homogenesis[x][y] = minify_vertices; 
                        }
                    }
                }
            }
        }

    }
    //testing
    cout << endl << "Homogenous transformed original graph vertices" << endl; // wypisywanie
    for (int i = 0; i < vertex_count; i++) {
        cout << i + 1 << "  " << tab_homogenesis[i][0] << " -> " << tab_homogenesis[i][1] << endl;
    }

    int original_vertex_max_count = 0;
    int countt = 0;
    int counter_x = 0;
    for (int i = 0; i < vertex_count; i++) { 
        for (int j = 0; j < 2; j++) {
            if (tab_homogenesis[i][j] > original_vertex_max_count) {
                original_vertex_max_count = tab_homogenesis[i][j];
            }
        }
    }
        int matrixxer[VerticesMax][VerticesMax];
        for (auto& i : matrixxer) {
            for (int& j : i) {
                j = 0;
            }
        }
    
    for(int i = 0; i < vertex_count; i++){
            matrixxer[tab_homogenesis[i][0]-1][tab_homogenesis[i][1]-1]++;
        }

        // writing to file
        filename = "T" + filename;
        ofstream out;
        out.open(filename.c_str());
        counter = 0;
        for (int i = 0; i < VerticesMax; i++) {
            if (counter < original_vertex_max_count) {
                out << i + 1;
            }
            for (int j = 0; j < VerticesMax; j++) {
                if (matrixxer[i][j] != 0) {
                    for (int x = 0; x < matrixxer[i][j]; x++) {
                        out << " " << j + 1;
                    }
                }
            }
            if (counter < original_vertex_max_count) {
                out << endl;
                counter++;
            }
        }
    print_results(filename);
}

void print_results(string filename) {
    ifstream in;
    in.open(filename);
    stringstream buffer;
    if (in.is_open()) {
        
        buffer << in.rdbuf();
        in.close();
    }
    else {
        throw runtime_error("Could not open file: " + filename);
    }
    cout << "Graf oryginalny H:" << endl;
    cout << buffer.str();
}
