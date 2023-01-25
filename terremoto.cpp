#include "terremoto.h"

// constructor
Terremoto::Terremoto(){
    dataOra = new char[DIM_DATAORA];
}

// copy constructor
Terremoto::Terremoto(const Terremoto &t){
    dataOra = new char[DIM_DATAORA];

    zona = t.zona;
    strcpy(dataOra, t.dataOra);
    profondita = t.profondita;
    magnitudo = t.magnitudo;
}

// destructor
Terremoto::~Terremoto(){
    delete dataOra;
}

// assignment constructor
Terremoto& Terremoto::operator=(const Terremoto &t){
    if (&t != this){
        zona = t.zona;
        strcpy(dataOra, t.dataOra);
        profondita = t.profondita;
        magnitudo = t.magnitudo;
    }
    return *this;
}

std::string Terremoto::getAnno() const{
    std::string dataOraString(dataOra);
    std::string anno = dataOraString.substr(0,4);
    return anno;
}

// overload >> in
std::istream& operator>>(std::istream &in, Terremoto &t){
    std::getline(in, t.zona, ',');
    in.getline(t.dataOra, DIM_DATAORA, ',');
    in >> t.profondita;
    in >> t.magnitudo;
    in.ignore();

    return in;
}

// overload << out
std::ostream& operator<<(std::ostream &out, const Terremoto &t)
{
    out << t.zona << ","
        << t.dataOra << ","
        << t.profondita << ","
        << t.magnitudo << std::endl;

    return out;
}

// overload confronto 
bool Terremoto::operator<(const Terremoto &other) const{
    int year = std::stoi(getAnno());
    int otherYear = std::stoi(other.getAnno());

    return year < otherYear;
}

// metodo push per LS
nodo* push_front(nodo *n, Terremoto t){
    nodo *temp;
    temp = new nodo;

    temp->value = t;
    temp->next = n;

    return temp;
}

nodo* carica_elenco(std::ifstream &in){
    nodo *n;
    Terremoto t;

    n = 0;
    while (in >> t){
        n = push_front(n, t);
    }
    return n;
}

void stampa_slist(std::ofstream &out, nodo* n){
    out << "---Stampo Lista Singola---\n\n";
    while (n && out){
        out << n->value;
        n = n->next;
    }
    out << "\n";
}

float media_magnitudo(nodo *n, std::string anno){
    float media = 0.0;
    int count = 0;

    while (n){
        if((n->value).getAnno() == anno){
            media += (n->value).getMagnitudo();
            count++;
        }
        n = n->next;
    }

    media /= count;
    return media;
}

void media_magnitudo_max(nodo *n){
    std::vector<std::string> annoSet;
    std::string tempAnno;
    std::string maxAnno;
    float maxMedia = 0.0;

    // complex computazionale O(n^2) poiché while itera n volte
    // * n iterazioni ad ogni find (attraversa tutta la lista)
    // meglio hashtable ma evito di implementarlo
    while (n){
        tempAnno = (n->value).getAnno();
        /* find(iterator inizio,
                iterator fine,
                elemento da cercare)
                == "end" significa "non trovato" 
                se non c'è, inserisci in vector,
                significa "ho già calcolato media
                per quest'anno",
                inoltre se è maggiore di quella
                corrente, settala come max temporanea
                poi si stampa*/
        if (std::find(annoSet.begin(), annoSet.end(), tempAnno) == annoSet.end()){
            annoSet.push_back(tempAnno);
            if (media_magnitudo(n, tempAnno) > maxMedia){
                maxMedia = media_magnitudo(n, tempAnno);
                maxAnno = tempAnno;
            }
        }
        n = n->next;
    }
    std::cout << "La media magnitudo massima (K = " << maxMedia <<
                ") si è verificata nel " << maxAnno << ".\n";
}

nodo* filtro_zona(nodo* n, std::string zona){
    nodo *n2 = 0;

    while (n){
        if ((n->value).getZona() == zona){
            n2 = push_front(n2, (n->value));
        }
        n = n->next;
    }
    return n2;
}

void singolo_to_doppio(nodo *n, std::list<Terremoto> &l){
    while (n){
        l.push_back(n->value);
        n = n->next;
    }
}

void stampa_dlist(std::ofstream &out, const std::list<Terremoto> &l){
    std::list<Terremoto> temp;
    // iteratore built-in di <list>
    std::list<Terremoto>::iterator iter;

    temp = l;

    out << "---Stampo Lista Doppia---\n\n";
    /* itera in tutto <list>
        ??? foreach ??? */
    for (iter = temp.begin(); iter != temp.end(); iter++){
        out << *iter;
    }
    out << "\n";
}

void stampa_recenti(std::ostream &out, const std::list<Terremoto> &l, int n){
    std::list<Terremoto> temp;
    std::list<Terremoto>::iterator iter;
    int count;

    temp = l;
    temp.sort();

    // come sopra
    for (iter = temp.begin(), count = 0; iter != temp.end() && count < n; iter++){
        out << *iter;
        count++;
    }
    out << std::endl;
}

void filtra_magnitudo(std::list<Terremoto> &l, float K)
{
    std::list<Terremoto>::iterator iter;

    iter = l.begin();

    while (iter != l.end()){
        if (iter->getMagnitudo() < K){
            // cancella per magnitudo < soglia
            iter = l.erase(iter);
        }
        else
            iter++;
    }
    if (iter == l.end())
        std::cout << "Lista doppia filtrata per K >= " << K << "\n";
}
