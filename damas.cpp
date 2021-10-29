// damas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <thread>


using namespace std;

vector <vector <int>> solucionesCompletas = {};
int cantSoluciones = 0;

void imprimirsol(int nreinas)
{

    ofstream file;
    file.open("solutions.txt");
    file << "#Solutions for "<<nreinas <<" queens \n";
    file << cantSoluciones << "\n";
    for (int i = 0; i < solucionesCompletas.size(); ++i) {
        for (int j = 0;j < solucionesCompletas[i].size();j++)
        {
            file << solucionesCompletas[i][j]<<" ";
        }
        file << "\n";
    }
    file.close();
}
void imprimirDot()
{
    
    ofstream file;
    file.open("graph.dot");
    file << "digraph D {"<< "\n";
    file << "node[shape = plaintext]" << "\n";
    file << "some_node[" << "\n";
    file << "label = <" << "\n";
    file << "<table border = \"0\" cellborder = \"1\" cellspacing = \"0\">" << "\n";
    
    for (int i = 0; i < solucionesCompletas[0].size(); ++i) {
        file << "<tr>";
        for (int j = 0;j < solucionesCompletas[0].size();j++)
        {
            if (j == solucionesCompletas[0][i])
            {
                file << "<td>&#9813; </td>";
            }
            else
                file << "<td> </td>";
        }
        file << "</tr> \n";
    }               
    file << "</table>>" << "\n";
    file << " ];" << "\n";
    file << " }" << "\n";
    file.close();
}

int coliciona(vector <int> elementos, int nuevapos)
{
    if (elementos.size() == 0)
    {
        return -1;
    }
    for (int i = 0; i < elementos.size(); ++i) {
        if (elementos[i] == nuevapos or nuevapos+elementos.size()==elementos[i]+i or nuevapos-elementos.size()==elementos[i]-i)
            return i;
    }

    return -1;
}

void nReinas( int cantReinasActu, int numReinas, int tamTabla, vector <int> solAnt)
{
    vector <thread> poolthreads;
    vector <int> tempo;

    if (cantReinasActu == numReinas)
    {
        cantSoluciones++;
        solucionesCompletas.push_back(solAnt);
    
    }
    else
    {
        return;
    }

    for (int i = 0;i < tamTabla;i++)
    {
        if (coliciona(solAnt, i) == -1 and cantReinasActu < numReinas)
        {
            tempo = solAnt;
            tempo.push_back(i);
            poolthreads.push_back(thread(nReinas, cantReinasActu + 1, numReinas, tamTabla, tempo));
            //nReinas(cantReinasActu+1, numReinas, tamTabla, tempo)

        }
        else return;
    }
    for (int i = 0; i < poolthreads.size(); i++)
    {
        poolthreads[i].join();
    }
}
void findReina(int cantReinasActu, int numReinas, vector <int> solAnt)
{
    vector <thread> poolthreads;
    vector <int> tempo;
    if(cantSoluciones>1)
    {
        return;
    }

    if (cantReinasActu == numReinas)
    {
        cantSoluciones++;
        solucionesCompletas.push_back(solAnt);
    }

    for (int i = 0;i < numReinas;i++)
    {
        if (coliciona(solAnt, i) == -1 and cantReinasActu < numReinas)
        {
            tempo = solAnt;
            tempo.push_back(i);
            poolthreads.push_back(thread(findReina, cantReinasActu + 1, numReinas, tempo));
            //nReinas(cantReinasActu+1, numReinas, tamTabla, tempo);

        }
    }
    for (int i = 0; i < poolthreads.size(); i++)
    {
        poolthreads[i].join();
    }
}

int main(int argc,char *argv[])
{
    
    string entrada = "-problemType";
    string entrada2 = "-N";
    string tProb;
    int nReina;
    if (argc != 5)
    {
        cout << "-problemType [all, find] -N <queens>" << endl;
        return 0;
    }
    for (int i = 1;i < argc;i++) {
        
        if (argv[i] == entrada) tProb=argv[i+1];
        if (argv[i] == entrada2) nReina = atoi(argv[i+1]);
    }

    if (tProb == "all") {
        vector<int> arr = {};
        nReinas( 0, nReina, nReina, arr);
        imprimirsol(nReina);
    }
    
    if (tProb == "find")
    {
        vector<int> arr = {};
        findReina(0, nReina, arr);
        imprimirDot();
    }

}
