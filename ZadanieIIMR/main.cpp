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

    //testing
    /*cout << "wypisywanie consequents vectora" << endl;
    for(int i=0;i<consequents.size();i++) {
        cout << consequents[i] << endl;
    }*/

    /*for (int i = 0; i < main_vector.size(); i++) { //rzedy
        for (int j = 0; j < main_vector[i].size(); j++) //kolumny
            cout << main_vector[i][j] << " ";
        cout << endl;
    }*/
    //for (int i = 0; i < VerticesMax; i++) {
    //    for (int j = 0; j < VerticesMax; j++) {
    //        matrix[i][j] = 0;
    //        /*cout << matrix[i][j];*/
    //    }
    //    /*cout << endl;*/
    //}

    /*for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }*/
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
    for(int x = 0; x < vertex_count-1;x++) { //po jednym rzędzie w tablicy
        for (int i = 1 + x; i < vertex_count - x; i++) { // porównujemy inny rząd
            bool match = false;
            bool mismatch = false;
            for (int j = 0; j < vertex_count; j++) { // porównujemy ich poszczególne elementy
                if (matrix[x][j] != matrix[i][j] && (matrix[x][j] == 1 || matrix[i][j] == 1)) {
                    mismatch = true; //oba rzędy mają przynajmniej jeden różny następnik
                }
                else if(matrix[x][j] == matrix[i][j] && matrix[x][j] == 1){
                    match = true; // oba rzędy mają przynajmniej jeden wspólny nastepnik
                }
            }
            if(match == mismatch){
                return false; // jezeli oba rzedy maja jakies nastepniki, ktore sa takie same i takie, ktore sa rozne
            }
        }
    }
    return true;
}

bool check_if_linear(int vertex_count, int matrix[VerticesMax][VerticesMax]){

    for(int x = 0; x < vertex_count-1;x++) {
        for (int i = 1 + x; i < vertex_count - x; i++) { 
            bool whole_matching = true;
            for (int j = 0; j < vertex_count; j++) { 
                if (matrix[x][j] != matrix[i][j] && (matrix[x][j] == 1 || matrix[i][j] == 1)) {
                    whole_matching = false;
                }
            }
            if(whole_matching){ 
                for (int j = 0; j < vertex_count; j++) { 
                    if (i != x && (matrix[j][i] == 1 && matrix[j][i] == matrix[j][x])) {
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

    // macierz przetransformowanych wierzcholkow na luki | zerwoy indeks to numer wierzcholka dla pomocy
    vector<array<int, TransValue> > tab(vertex_count);

    for (int i = 0; i < vertex_count; i++) {// wyzerowanie nowo powstalej macierzy
        for (int j = 0; j < TransValue; j++) {
            tab[i][j] = 0;
        }
    }

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 1; j < TransValue; j++) {
            tab[i][j] = counter++;
        }
    }
    /*cout << "Transformed graph in array: " << endl;
    for (int i = 0; i < vertex_count; i++) {
        cout << tab[i][0] << "\t" << tab[i][1] << " -> " << tab[i][2] << endl;
    }*/

    // transforming vertices to links via finding egligible matrix positions
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
    //trying to get homogenous array with minimal index of vertices
    vector<array<int, 2> > tab_homogenesis(vertex_count);
    int minify_vertices = 0;
    int helper_variable;



    // making a temporarty table and zeroing it
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < 2; j++) {
            tab_homogenesis[i][j] = tab[i][j + 1];
            tab_homogenesis[i][j] += 50;
            //cout << tab[i][j] << endl;
        }
    }
    cout << endl;
    for (int i = 0; i < vertex_count; i++) { //dla kazdego rzedu
        for (int j = 0; j < 2; j++) { //w kazdej kolumnie
            if (tab_homogenesis[i][j] > minify_vertices) {
                helper_variable = tab_homogenesis[i][j]; // przypisz wartosc z tej komorki pomocniczej zmienne
                minify_vertices++;
                for (int x = 0; x < vertex_count; x++) { // dla kazdego rzedu
                    for (int y = 0; y < 2; y++) { // w kazdej kolumnie
                        if (tab_homogenesis[x][y] ==
                            helper_variable) { // sprawdz czy wartosc z pomocniczej zmiennej jest rowna danemu wierzcholkowi
                            tab_homogenesis[x][y] = minify_vertices; // jesli tak, to wpisz w nowej tabeli najmniejsz
                            // dostepna wartosc zamiast tej pierowtnej
                        }
                    }
                }
            }
        }

    }
    cout << endl << "Homogenous transformed original graph vertices" << endl; // wypisywanie
    for (int i = 0; i < vertex_count; i++) {
        cout << i << "  " << tab_homogenesis[i][0] << " -> " << tab_homogenesis[i][1] << endl;
    }
    // sorting the the output of original graph
    int original_vertex_max_count = 0;
    int countt = 0;
    int counter_x = 0;
    for (int i = 0; i < vertex_count; i++) { //liczymy ilosc wierzchokow w grafie oryginalnym
        for (int j = 0; j < 2; j++) {
            if (tab_homogenesis[i][j] > original_vertex_max_count) {
                original_vertex_max_count = tab_homogenesis[i][j];
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
        filename = "T" + filename; //plik do zapisu bedzie mial taka sama nazwe co oryginalny z dopisanieT na poczatku nazwy
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
