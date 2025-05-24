#include <iostream>
#include <locale.h>
#define TAM 9

using namespace std;

struct PilhaImpar
{
	int numeros[TAM];
	int qtd;
};

struct Par
{
	int numero;
	struct Par *ant;

};

struct PilhaPar
{
	Par *topo;
};

PilhaImpar* initImpar()
{
	PilhaImpar* p = new PilhaImpar;
	p->qtd = 0;

	return p;
}

PilhaPar* initPar()
{
	PilhaPar* p = new PilhaPar;
	p->topo = NULL;

	return p;
}

bool isEmpty(PilhaImpar* p)
{

	return (p->qtd == 0);
}

bool isEmpty(PilhaPar* p)
{

	return (p->topo == NULL);
}
bool push(PilhaImpar* p, int num)
{

	bool podeEmpilhar = (p->qtd < TAM);
	if (podeEmpilhar)
	{
		p->numeros[p->qtd++] = num;
	}
	return podeEmpilhar;
}

void push(PilhaPar* p, int num)
{

	Par* par = new Par;
	par->numero = num;
	par->ant = p->topo;
	p->topo = par;

}

int pop(PilhaImpar* p)
{

	int ret;
	if (isEmpty(p))
	{
		ret = -1;
	}
	else
	{
		ret = p->numeros[p->qtd - 1];
		p->qtd--;
	}

	return ret;
}
int pop(PilhaPar* p)
{

	int ret;
	if (isEmpty(p))
	{
		ret = -1;
	}
	else
	{
		Par* par = p->topo;
		ret = par->numero;
		p->topo = p->topo->ant;
		free(par);

	}
	return ret;
}

void popPilhas(PilhaPar* pares, PilhaImpar* impares)
{

	for (int ii = 0; ii < TAM; ii++)
	{
		if (isEmpty(pares)) {
			cout << "Desempilhando impar: " << pop(impares) << endl; 
		}
		else if (isEmpty(impares)) {
			cout << "Desempilhando par: " << pop(pares) << endl;
		}
		else if (pares->topo->numero < impares->numeros[impares->qtd - 1]) {
			cout << "Desempilhando impar: " << pop(impares) << endl; 
		}
		else {
			cout << "Desempilhando par: " << pop(pares) << endl;
		}
	}
}

bool numValido(int num, int ant)
{

	return (num > 0 && num > ant);
}


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	PilhaImpar* pilhaImpar = initImpar();
	PilhaPar* pilhaPar = initPar();
	int numAnterior = 0;

	for(int ii = 0; ii < TAM; ii++)
	{
		int numAtual;
		cout << "Digite um número inteiro: " << endl;
		cin >> numAtual;
		cin.ignore(1000, '\n');
		while(!numValido(numAtual, numAnterior))
		{
			cout << "Precisa ser maior que zero e maior que o número anterior!" << endl;
			cout << "Digite um número inteiro: " << endl;
			cin >> numAtual;
			cin.ignore(1000, '\n');
		}
		if (numAtual%2 == 0) {
			push(pilhaPar, numAtual);
			cout << "num empilhado: " << pilhaPar->topo->numero << endl;
		}
		else {
			cout << "empilhou em " << pilhaImpar->qtd -1 << push(pilhaImpar, numAtual) <<  endl;
			cout << "num empilhado " << pilhaImpar->numeros[pilhaImpar->qtd - 1] << endl;
		}
		numAnterior = numAtual;
	}
	popPilhas(pilhaPar, pilhaImpar);
	
	return 0;
}
