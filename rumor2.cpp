#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>

using namespace std;
#define stepMax 10000
#define lambda 100

class Node
{
	private:
		int awareness; // -1 = S, 0 = R, 1 = I
		int pos; // posição, auxiliar
	public:
		vector<int> neighbors;
		Node(int awareness)
		{
			pos=-999;
			this->awareness=awareness;
		}

		int getAwareness()
		{
			return awareness;
		}

        int getSize()
		{
			return neighbors.size();
		}

		int setAwareness(int awareness)
		{
			this->awareness=awareness;
		}

		void setPos(int pos)
		{
			this->pos=pos;
		}

		int getPos()
		{
			return pos;
		}

		void addNeighbor(int a)
		{
			neighbors.push_back(a);
		}

		void printNeighbors()
		{
			for(int i = 0 ; i < neighbors.size() ; i++)
				cout << " " << neighbors[i];
		}

};

class Graph
{
/*
	private:

		int counter;
		int ignorant;
		int stifler;
		int spreader;
		vector<Node*> graph;
		string cor;

	public:

		Graph(string cor)
		{
			counter=0;
			stifler=0;
			spreader=0;
			for(int i = 0 ; i < 10000 ; i++) // ajustar
			{
				addNode(new Node(-1));
			}
			this->cor=cor;
			ignorant=graph.size();
		}

		void spreadInit(double i)
		{
			if(graph.size()>0)
			{
				do
                {
                    int chosen = rand()%graph.size();
                    if(graph[chosen]->getAwareness()==-1)
                    {
                        graph[chosen]->setAwareness(0);
                        spreader++;
                        ignorant--;
                    }
                }while(i>getSpreaderPercent());
			}
			else
			{
				cerr << "Grafo Vazio!" << endl;
			}
		}

        void addNode(Node* A)
		{
			A->setPos(counter);
			graph.push_back(A);
			counter++;
		}

		void addNeighbor(int src, int des)
		{
			graph[src]->addNeighbor(des);
			//
			graph[des]->addNeighbor(src);
		}

		int getSpreader()
		{
			return spreader;
		}

		int getIgnorant()
		{
			return ignorant;
		}

		int getStifler()
		{
			return stifler;
		}

		double getSpreaderPercent()
		{
            double spreaderPercent = (double) (spreader);
            spreaderPercent = spreaderPercent/graph.size();
			return spreaderPercent;
		}

		double getIgnorantPercent()
		{
			double ignorantPercent = (double) (ignorant);
			ignorantPercent = ignorantPercent/graph.size();
			return ignorantPercent;
		}

		double getStiflerPercent()
		{
			double stiflerPercent = (double) (stifler);
			stiflerPercent = stiflerPercent/graph.size();
			return stiflerPercent;
		}

		vector<Node*> getSpreadingList()
		{
		    vector<Node*> awareList;
            for(int i =0 ; i < graph.size() ; i++)
			{
				if(graph[i]->getAwareness()==0)
				{
					awareList.push_back(graph[i]);
				}
			}
			return awareList;
		}
*/
        void spreadContact(int escolhido, vector<Node*> awareList, double mi)/** -1 ignorant 0 spreader 1 stifler*/
		{
		    int tam = awareList[escolhido]->neighbors.size();
		    if(tam>0)
            {
                int chosenOne = rand()%tam;
                int tryToSpread = rand()%100 + 1;
                Node* neighbor = graph[awareList[escolhido]->neighbors[chosenOne]];
                Node* oneself = awareList[escolhido];
                if(neighbor->getAwareness()==0)
                {
                    if(tryToSpread<= mi)
                    {
                        oneself->setAwareness(1);
                        spreader--;
                        stifler++;
                    }
                }
                if(neighbor->getAwareness()==1)
                {
                    if(tryToSpread<= mi)
                    {
                        oneself->setAwareness(1);
                        spreader--;
                        stifler++;
                    }
                }
                if(neighbor->getAwareness()==-1)
                {
                    if(tryToSpread<= lambda)
                    {
                        neighbor->setAwareness(0);
                        ignorant--;
                        spreader++;
                    }
                }
            }

		}

		void spreadTruncated(int escolhido, vector<Node*> awareList, double mi)
		{
            bool isSpreader = true;
            for(int j = 0 ; j < awareList[escolhido]->neighbors.size() ; j++)
            {
                if(isSpreader)
                {
                    int tryToSpread = rand()%100 + 1;
                    Node* neighbor = graph[awareList[escolhido]->neighbors[j]];
                    Node* oneself = awareList[escolhido];


                    if(neighbor->getAwareness()==0)
                    {
                        if(tryToSpread<= mi)
                        {
                            oneself->setAwareness(1);
                            spreader--;
                            stifler++;
                            isSpreader = false;
                        }
                    }
                    if(neighbor->getAwareness()==1)
                    {
                        if(tryToSpread<= mi)
                        {
                            oneself->setAwareness(1);
                            spreader--;
                            stifler++;
                            isSpreader = false;
                        }
                    }

                    if(neighbor->getAwareness()==-1)
                    {
                        if(tryToSpread<= lambda)
                        {
                            neighbor->setAwareness(0);
                            ignorant--;
                            spreader++;
                        }
                    }
                }
            }

		}

		void spreadReactive(int escolhido, vector<Node*> awareList, double mi)
		{
            bool isSpreader = true;
            for(int j = 0 ; j < awareList[escolhido]->neighbors.size() ; j++)
            {
                int tryToSpread = rand()%100 + 1;
                Node* neighbor = graph[awareList[escolhido]->neighbors[j]];
                Node* oneself = awareList[escolhido];


                if(neighbor->getAwareness()==0)
                {
                    if(tryToSpread<= mi)
                    {
                        oneself->setAwareness(1);
                        isSpreader = false;
                    }
                }
                if(neighbor->getAwareness()==1)
                {
                    if(tryToSpread<= mi)
                    {
                        oneself->setAwareness(1);
                        isSpreader = false;
                    }
                }

                if(neighbor->getAwareness()==-1)
                {
                    if(tryToSpread<= lambda)
                    {
                        neighbor->setAwareness(0);
                        ignorant--;
                        spreader++;
                    }
                }
            }
            if(!isSpreader)
            {
                spreader--;
                stifler++;
            }
		}

		void spreadRun(double mi)
		{
            vector<Node*> awareList = getSpreadingList();
            if(awareList.size()!=0)
			{
                for(int i = 0; i < awareList.size(); i++)
                {
                    if(getCor().compare("C")==0)
                    {
                        spreadContact(i,awareList,mi);
                    }
                    else
                    {
                        if(getCor().compare("R")==0)
                        {
                            spreadReactive(i,awareList,mi);
                        }
                        else
                        {
                            if(getCor().compare("T")==0)
                            {
                                spreadTruncated(i,awareList,mi);
                            }
                            else
                            {
                                cerr << "Algo de errado nao esta certo." << endl << endl;
                            }
                        }
                    }
                }
			}
		}

		void healAll()
		{
			for(int i = 0 ; i < graph.size() ; i++)
			{
				graph[i]->setAwareness(-1);
			}
			spreader=0;
			stifler=0;
            ignorant=graph.size();
		}


		int getCounter() // Não utilizado - Para Debug
		{
			return counter;
		}

		string getCor() // Não utilizado - Para Debug
		{
			return cor;
		}

		int getSize() // Não utilizado - Para Debug
		{
			return graph.size();
		}

		vector<Node*> getGraph() // Não utilizado - Para Debug
		{
			return graph;
		}

};

double getTail(vector<double> listA, double graphSize)
{
    double mean = 0.0;
    int tam = listA.size();
    int tail = (int)tam*0.05;
    int start = tam-tail;
    for(int j = start ; j < tam ; j++)
    {
        mean = mean + listA[j];
    }
    if(mean==0.0)
    {
        mean=0.0;
    }
    else
    {
        mean/=tail;
    }

    mean/=graphSize;

    return mean;
}

vector<double> listNormalize(vector<double> listA, double norm)
{
    for(int i = 1; i < listA.size() ; i++)
    {
        int aux = listA[i]/norm;
        listA[i] = aux;
    }
    return listA;
}

void listPrint(vector<double> listA)
{
    for(int i = 0; i < listA.size() ; i++)
    {
        cout << "i: " << i << " n: " <<  listA[i] << endl;
    }
}

vector<double> listInit()
{
    vector<double> listA;
    for(int i = 0; i < 10000 ; i++)
    {
        listA.push_back(0);
    }
    return listA;
}

void logOut(Graph* G, float mi, string thirdPart, vector<double> listA)
{

    string firstPart, secondPart;
    string format = ".txt";
    if(G->getCor().compare("C")==0)
    {
        firstPart="Rumor_C_Mi_";
    }
    else if(G->getCor().compare("R")==0)
    {
        firstPart="Rumor_R_Mi_";
    }
    else
    {
        firstPart="Rumor_T_Mi_";
    }
    ostringstream convert;
    convert << mi;
    secondPart = convert.str();

    string final = firstPart + secondPart + thirdPart + format;
    const char * finalOut = final.c_str();
    FILE* pFileOut;
    pFileOut=fopen(finalOut,"w");
    if(pFileOut==NULL)
    {
        cerr << "Falha ao abrir arquivo." << endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < listA.size(); i++)
    {
        fprintf(pFileOut, "%d %lf\n", i, listA[i]);
    }
}


int main()
{

    /* Início do Main, Declaração de Variáveis */

    int veof; // Auxiliar para o descritor de arquivos

    double initialSeed = 0.05; // Semente Inicial para Início da Epidemia
    string type, type2; // SIR OR SIS
	FILE* pFileIn; // Descritor de arquivos de entrada
	Graph* G; // Grafo base
    srand(time(NULL)); // Semente do Random Number

//#############################################################################

    /*
        Arquivo de entrada

        Formato utilizado:
        X   Y   Z
        X   Y   Z
        X   Y   Z
        X = nó origem possui aresta com Y = nó destino,
        Z é utilizado para finalizar a leitura do arquivo, 1 = continua, 0 = pare
    */

	pFileIn=fopen("netfinal.txt","r");
	if(pFileIn==NULL)
	{
		printf("\033c");
		cerr << "Falha ao abrir arquivo." << endl;
		exit(EXIT_FAILURE);
	}

//#############################################################################

    cout << "Escreva o tipo de transmissao - Contato, Reativo ou Truncado(C/R/T[Nimplem]: ";
	cin >> type2;

	/* Inicialização do Grafo */

    if(type2.compare("C")==0)
    {
        G = new Graph("C");
    }
    else
    {
        if(type2.compare("R")==0)
        {
            G = new Graph("R");
        }
        else
        {
            G = new Graph("T");
        }
    }

    //cout << "wtf: " << G->getCor() << " size: " << G->getSize() << endl << endl;
	/* Leitura do arquivo e criação dos nós */

	do
	{
		int a, b;
		fscanf(pFileIn,"%d",&a);
		fscanf(pFileIn,"%d",&b);
		fscanf(pFileIn,"%d",&veof);
		G->addNeighbor(a,b);
	}while(veof==0);

    int aux = 0;
    vector<double> vpersistenceSt;
    vector<double> vpersistenceSp;
    vector<double> vpersistenceIg;
    vector<double> vbeta;
    for(int i = 10 ; i < 101 ; i+=10 ) // variaçao de mi / alfa
    {
        vector<double> nSp = listInit();
        vector<double> nSt = listInit();
        vector<double> nIg = listInit();
        for(int j = 0; j < 10 ; j++ )
        {
            G->healAll();
            int step = 0;
            nSp[0]=G->getSpreader();
            nSt[0]=G->getStifler();
            nIg[0]=G->getIgnorant();
            step++;
            G->spreadInit(initialSeed); // Primeiros infectados
            nSp[step]=nSp[step]+G->getSpreader();
            nSt[step]=nSt[step]+G->getStifler();
            nIg[step]=nIg[step]+G->getIgnorant();
            step++;
            while(step < 10000)
            {
                if(G->getSpreader()>0)
                {
                    G->spreadRun(i);
                }
                nSp[step]=nSp[step]+G->getSpreader();
                nSt[step]=nSt[step]+G->getStifler();
                nIg[step]=nIg[step]+G->getIgnorant();
                step++;
            }
        }
        vector<double> nSp_F = listNormalize(nSp,10.0);
        vector<double> nSt_F = listNormalize(nSt,10.0);
        vector<double> nIg_F = listNormalize(nIg,10.0);
        //listPrint(nIg_F);
        double meanSp = getTail(nSp_F,G->getSize());
        double meanSt = getTail(nSt_F,G->getSize());
        double meanIg = getTail(nIg_F,G->getSize());
        vpersistenceSp.push_back(meanSp);
        vpersistenceSt.push_back(meanSt);
        vpersistenceIg.push_back(meanIg);
        double b = (double)i;
        vbeta.push_back(b/100);
        logOut(G,b/100,"_Spreaders",nSp_F);
        logOut(G,b/100,"_Stiflers",nSt_F);
        logOut(G,b/100,"_Ignorants",nIg_F);
        //cout << "alfa: " << vbeta[aux] << " | Sp pers: " << vpersistenceSp[aux] << " | St pers: " << vpersistenceSt[aux] << " | Ig pers: " << vpersistenceIg[aux] << endl;
        //cout << endl << endl << "Final: Stiflers: " << G->getStifler() << " Spreaders: " << G->getSpreader() << " Ignorants: " << G->getIgnorant() << endl;
        aux++;
    }
//#############################################################################

    cout << "\n\nPrograma finalizado com sucesso";

//#############################################################################

    exit(EXIT_SUCCESS);
	return 0;
}


