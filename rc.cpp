#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
#define stepMax 1000
#define graphSize 200 // mudar para o arquivo de config
int mi;
int gama;
int alfa;
int corr;
int lambda;

class Node
{
	private:
		int status; // -1 = S, 0 = R, 1 = I
		int pos; // posição, auxiliar
	public:
		vector<int> neighbors;
		Node(int status)
		{
			pos=-999;
			this->status=status;
		}

		int getStatus()
		{
			return status;
		}

        int getSize()
		{
			return neighbors.size();
		}

		int setStatus(int status)
		{
			this->status=status;
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
	private:

		int counter;
		int infected;
		int ignorant;
		int stifler;
		int spreader;
		vector<Node*> epidemicLayer;
		vector<Node*> informationLayer;
		bool sir;
		bool cor;

	public:
		Graph(bool sir, bool cor, int nNodes)
		{
			counter=0;
			infected=0;
			stifler=0;
			spreader=0;
			for(int i = 0 ; i < nNodes ; i++) // ajustar
			{
				addNode(new Node(-1),new Node(-1));
			}
			this->sir=sir;
			this->cor=cor;
			ignorant=informationLayer.size();
		}

		/** Função addNode
            Adiciona os nós aos grafos das redes
        */

        void addNode(Node* A,Node* B)
		{
			A->setPos(counter);
			B->setPos(counter);
			epidemicLayer.push_back(A);
			informationLayer.push_back(B);
			counter++;
		}

		void addNeighbor(int src, int des, string layer, bool directed)
		{
		    if(layer.compare("information")==0)
            {
                informationLayer[src]->addNeighbor(des);
                if(!directed) informationLayer[des]->addNeighbor(src);
            }
            else
            {
                epidemicLayer[src]->addNeighbor(des);
                if(!directed) epidemicLayer[des]->addNeighbor(src);
            }

		}

		int getCounter() // Não utilizado - Para Debug
		{
			return counter;
		}

		void infectInit(double i)
		{
			if(epidemicLayer.size()>0)
			{
				do
                {
                    int chosen = rand()%epidemicLayer.size();
                    if(epidemicLayer[chosen]->getStatus()==-1)
                    {
                        epidemicLayer[chosen]->setStatus(1);
                        infected++;
                    }
                }while(i>infectedTotalPercent());
			}
			else
			{
				cerr << "Grafo Vazio!" << endl;
			}
		}

		void spreadInit(double i)
		{
			if(informationLayer.size()>0)
			{
				do
                {
                    int chosen = rand()%informationLayer.size();
                    if(informationLayer[chosen]->getStatus()==-1)
                    {
                        informationLayer[chosen]->setStatus(0);
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

		vector<Node*> getEpidemicLayer() // Não utilizado - Para Debug
		{
			return epidemicLayer;
		}

		vector<Node*> getInformationLayer() // Não utilizado - Para Debug
		{
			return informationLayer;
		}

		int getInfected()
		{
			return infected;
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
            spreaderPercent = spreaderPercent/informationLayer.size();
			return spreaderPercent;
		}

		double getIgnorantPercent()
		{
			double ignorantPercent = (double) (ignorant);
			ignorantPercent = ignorantPercent/informationLayer.size();
			return ignorantPercent;
		}

		double getStiflerPercent()
		{
			double stiflerPercent = (double) (stifler);
			stiflerPercent = stiflerPercent/informationLayer.size();
			return stiflerPercent;
		}

		void printList() // Não utilizado - Para Debug
		{
			for(int i = 0 ; i < epidemicLayer.size() ; i++)
			{
				cout << "\nNode " << i << "\nstatus: " << epidemicLayer[i]->getStatus() << "\nVizinhos: ";
				epidemicLayer[i]->printNeighbors();
			}
		}

		void printState() // Não utilizado - Para Debug
		{
			for(int i = 0 ; i < epidemicLayer.size() ; i++)
			{
				cout << "\nNode " << i << " esta: ";
				if(epidemicLayer[i]->getStatus()==-1)
					cout << "suscetível";
				if(epidemicLayer[i]->getStatus()==0)
					cout << "recuperado";
				if(epidemicLayer[i]->getStatus()==1)
					cout << "infectado";

			}
		}

		int getInfectedDebug() // Não utilizado - Para Debug
		{
            int aux = 0;
			for(int i = 0 ; i < epidemicLayer.size() ; i++)
			{
			    if(epidemicLayer[i]->getStatus()==1)
                    aux += 1;
			}
			return aux;
		}

		float infectedTotalPercent()
		{
		    float aux = (float)infected;
            return aux/epidemicLayer.size();
		}

		void healAll()
		{
			for(int i = 0 ; i < epidemicLayer.size() ; i++)
			{
				epidemicLayer[i]->setStatus(-1);
			}
			infected=0;
		}

		vector<Node*> getInfectedList()
		{
		    vector<Node*> infList;
            for(int i =0 ; i < epidemicLayer.size() ; i++)
			{
				if(epidemicLayer[i]->getStatus()==1)
				{
					infList.push_back(epidemicLayer[i]);
				}
			}
			return infList;
		}

		vector<Node*> getSpreadingList()
		{
		    vector<Node*> awareList;
            for(int i =0 ; i < informationLayer.size() ; i++)
			{
				if(informationLayer[i]->getStatus()==0)
				{
					awareList.push_back(informationLayer[i]);
				}
			}
			return awareList;
		}

        void infectContact(int escolhido, vector<Node*> infectedList, float beta)
		{
		    int tam = infectedList[escolhido]->neighbors.size();
		    if(tam>0)
            {
                int chosenOne = rand()%tam;
                int tryToInfect = rand()%100 + 1;
                if(epidemicLayer[infectedList[escolhido]->neighbors[chosenOne]]->getStatus()==-1 && ( tryToInfect <= beta))
                {
                    epidemicLayer[infectedList[escolhido]->neighbors[chosenOne]]->setStatus(1); // infecta
                    infected++;
                }
            }

		}

		void infectReactive(int escolhido, vector<Node*> infectedList, float beta)
		{
            for(int j = 0 ; j < infectedList[escolhido]->neighbors.size() ; j++)
            {
                    int tryToInfect = rand()%100 + 1;
                    if((epidemicLayer[infectedList[escolhido]->neighbors[j]])->getStatus()==-1 && ( tryToInfect <= (beta)))
                    {
                        (epidemicLayer[infectedList[escolhido]->neighbors[j]])->setStatus(1); // infecta
                        infected++;
                    }
            }

		}

		void heal(int escolhido, vector<Node*> infectedList)
		{
			int chosen = escolhido;
			int tryToHeal = rand()%100 + 1;
			if(tryToHeal <= mi)
			{
				if(sir)
				{
					infectedList[chosen]->setStatus(0); //sir
				}
				else
				{
					infectedList[chosen]->setStatus(-1); //sis
				}
				//cout << "\nO node " << infectedList[chosen]->getPos() << " se recuperou.";
				infected--;
			}
		}

		int infectRun(float beta)
		{
            vector<Node*> infectedList = getInfectedList();
            if(infectedList.size()!=0)
			{
				for(int i = 0; i < infectedList.size(); i++)
                {
                    heal(i,infectedList); // permite reinfecção
                }
                for(int i = 0; i < infectedList.size(); i++)
                {
                    if(cor)
                    {
                        infectContact(i,infectedList,beta);
                    }
                    else
                    {
                        infectReactive(i,infectedList,beta);
                    }
                }
			}
			return getInfected();
		}

};


void loadConfig()
{
    ifstream config("config.txt");
    string line, dummy;
    int nLine=1;
    if (config.is_open())
    {
        while ( getline (config,line) )
        {
            if(nLine>3&&nLine<10)
            {
                istringstream iss(line);
                iss >> dummy;
                if(nLine==4)
                    iss >> mi;
                else if(nLine==5)
                    iss >> gama;
                else if(nLine==6)
                    iss >> alfa;
                else if(nLine==7)
                    iss >> corr;
                else if(nLine==8)
                    iss >> lambda;
                else if(nLine==9)
                    iss >> graphSize;
            }
            nLine++;
        }
        config.close();
    }
    else
    {
        cout << "O arquivo config.txt nao foi encontrado ou esta corrupto" << endl;
    }
}




/**

    Main -

*/

int main()
{

    /* Atribuição de Variáveis Globais */

    mi = 0;
    gama = 0;
    alfa = 0;
    corr = 1;
    lambda = 0;
    graphSize = 0;
    loadConfig();
    /* Início do Main, Declaração de Variáveis */

    int veof; // Auxiliar para o descritor de arquivos

    double initialSeed = 0.05; // Semente Inicial para Início da Epidemia
    char* saidaTxt;
	FILE* pFileInEpidemic; // Descritor de arquivos de entrada
	FILE* pFileInInformation; // Descritor de arquivos de entrada
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

	pFileInEpidemic=fopen("netf.txt","r");
	if(pFileInEpidemic==NULL)
	{
		printf("\033c");
		cerr << "Falha ao abrir arquivo." << endl;
		exit(EXIT_FAILURE);
	}

	pFileInInformation=fopen("netf.txt","r");
	if(pFileInInformation==NULL)
	{
		printf("\033c");
		cerr << "Falha ao abrir arquivo." << endl;
		exit(EXIT_FAILURE);
	}

//#############################################################################


	/* Inicialização do Grafo */

	if(!mi)
    {
        if(corr)
        {
            G = new Graph(true,true,graphSize);
        }
        else
        {
            G = new Graph(true,false,graphSize);
        }
    }
    else
    {
        if(corr)
        {
            G = new Graph(false,true,graphSize);
        }
        else
        {
            G = new Graph(false,false,graphSize);
        }
    }

	/* Leitura do arquivo e criação dos nós */

	do
	{
		int a, b;
		fscanf(pFileInEpidemic,"%d",&a);
		fscanf(pFileInEpidemic,"%d",&b);
		fscanf(pFileInEpidemic,"%d",&veof);
		G->addNeighbor(a,b,"epidemic",0);
	}while(veof==0);

	do
	{
		int a, b;
		fscanf(pFileInInformation,"%d",&a);
		fscanf(pFileInInformation,"%d",&b);
		fscanf(pFileInInformation,"%d",&veof);
		G->addNeighbor(a,b,"information",0);
	}while(veof==0);

    int aux = 0;
    vector<float> vpersistence;
    vector<float> vbeta;
    for(int i = 0 ; i < 95 ; i+=5 )
    {
        G->healAll();
        vector<float> n_Infected; // Vector para Amostra de Nro Infectados
        int step = 1; // Contador de passos
        G->infectInit(initialSeed); // Primeiros infectados
        //cout << G->getInfected() << endl << endl; // debug func

        n_Infected.push_back(G->getInfected());
        do
        {
            if(step!=1)
            {
                if(G->getInfected()>0)
                {
                    n_Infected.push_back(G->infectRun(i));
                    //G->printState(); DEBUG FUNC
                }
                else
                {
                    break;
                }
            }
            step++;
        }while(step<stepMax);

        int tam = n_Infected.size();
        int au = (int)tam*0.05;
        float mean = 0;
        for(int j = tam-au ; j < tam ; j++)
        {
            mean = mean + n_Infected[j];
        }
        float v = (float)mean;
        if(mean==0)
        {
            mean=0;
        }
        else
        {
            mean/=au;
            mean/=200;
        }
        vpersistence.push_back(mean);
        float b = (float)i;
        b/=100;
        vbeta.push_back(b);
        cout << "beta: " << vbeta[aux] << " persitence: " << vpersistence[aux] << endl;
        aux++;
    }


    /**
	Modelo de saída para Windows
	*/

	if(!mi)
	{
        if(corr)
        {
            saidaTxt="SIRC.txt";
        }
        else
        {
            saidaTxt="SIRR.txt";
        }
	}
	else
	{
        if(corr)
        {
            saidaTxt="SISC.txt";
        }
        else
        {
            saidaTxt="SISR.txt";
        }
	}
    FILE* pFileOut;
    char* end = (char*)saidaTxt;
    pFileOut=fopen(saidaTxt,"w");
    if(pFileOut==NULL)
    {
        cerr << "Falha ao abrir arquivo." << endl;
        exit(EXIT_FAILURE);
    }
    //for(int i = 0 ; i < n_Infected.size() ; i++)
    //{
     //   fprintf(pFileOut,"%d %d\n", i, n_Infected[i]);
    //}

    cout << "\n\nPrograma finalizado com sucesso";

//#############################################################################

    exit(EXIT_SUCCESS);
	return 0;
}


