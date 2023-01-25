#include "terremoto.h"

int main(){
    std::string filename, zona;
    std::ifstream in_stream;
    std::ofstream out_stream;
    nodo *elenco, *filtroZona;
    std::list<Terremoto> elencoDoppio;
    int n;
    float K;

    // caricamento dati tramite file
    std::cout << "Inserire nome file da caricare\n";
    getline(std::cin, filename);
    in_stream.open(filename);

    // elenco è la linked list con tutti i terremoti
    elenco = carica_elenco(in_stream);
    in_stream.close();

    // apri file per ofstream
    out_stream.open("output.txt");

    // filtro per zone tramite input da tastiera
    std::cout << "Inserire zona da filtrare\n";
    std::cin >> zona;
    filtroZona = filtro_zona(elenco, zona);

    // stampa lista singola
    stampa_slist(out_stream, filtroZona);

    // copia di elenco in una double linked list (elencoDoppio)
    singolo_to_doppio(elenco, elencoDoppio);
    
    // stampa N terremoti più recenti
    std::cout << "Inserire numero di terremoti da stampare in ordine\n";
    std::cin >> n;
    stampa_recenti(std::cout, elencoDoppio, n);

    // filtro per soglia di magnitudo tramite input da tastiera
    std::cout << "Inserire soglia magnitudo (filtra per >=K)\n";
    std::cin >> K;
    filtra_magnitudo(elencoDoppio, K);

    // stampa lista doppia
    out_stream << "(Lista doppia filtrata per Magnitudo >= " << K << ")\n";
    stampa_dlist(out_stream, elencoDoppio);

    // stampa anno con media magnitudo max
    media_magnitudo_max(elenco);

    return 0;
}