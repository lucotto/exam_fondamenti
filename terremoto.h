#ifndef TERREMOTO_H
#define TERREMOTO_H

#include <iostream>     // stream
#include <string>       // std::string
#include <cstring>      // strcpy
#include <fstream>      // stream file
#include <vector>       // vector
#include <list>         // liste doppie
#include <algorithm>    // metodo find su per vector

// capienza array daat/ora
const int DIM_DATAORA = 20;

class Terremoto{
    public:
        Terremoto();
        Terremoto(const Terremoto &t);
        ~Terremoto();
        Terremoto& operator=(const Terremoto &t);
        bool operator<(const Terremoto &other) const;

        void getDataOra(char *str) const {std::strcpy(str, dataOra);}
        int getProfondita() const {return profondita;}
        float getMagnitudo() const {return magnitudo;}
        std::string getZona() const {return zona;}
        std::string getAnno() const; 
    
    private:
        std::string zona;
        char* dataOra;      // 19 lettere "aaaa-mm-gg hh:mm:ss"
        int profondita;     
        float magnitudo;    // intervallo (0.0, 10.0)

    friend std::istream& operator>>(std::istream &in, Terremoto &t);
    friend std::ostream& operator<<(std::ostream &out, const Terremoto &t);
};

// implementazione lista singola
struct nodo{
    Terremoto value;
    nodo *next;
};

/* ----------------------------------- 
    FUNZIONI STREAM IO - STANDARD/FILE
   ----------------------------------- */
// carica elenco da file
nodo* carica_elenco(std::ifstream &in);
// stampa lista singola
void stampa_slist(std::ofstream &out, nodo* n);
// stampa lista doppia
void stampa_dlist(std::ofstream &out, const std::list<Terremoto> &l);
// stampa n più recenti da lista doppia (prevede sort)
void stampa_recenti(std::ostream &out, const std::list<Terremoto> &l, int n);

/* ----------------
    ALTRE FUNZIONI
   ---------------- */
// converte lista singola in doppia
void singolo_to_doppio(nodo *n, std::list<Terremoto> &l);
// media magnitudo su LS in dato anno
float media_magnitudo(nodo *n, std::string anno);
// media magnitudo generale
void media_magnitudo_max(nodo *n);
// filtra per zona da LS
nodo* filtro_zona(nodo* n, std::string zona);
// filtra per magnitudo da LD
void filtra_magnitudo(std::list<Terremoto> &l, float K);

#endif