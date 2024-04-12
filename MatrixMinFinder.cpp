// C++ Program to toggle string 
#include <cstring> 
#include <iostream> 
#include <vector>
#include <random>                                       // pour les fonctions de g�n�ration de nombres al�atoires


using namespace std;
// D�finition du type de la matrice
using Matrix = std::vector<std::vector<float>>;

// D�claration des valeurs initiales de x_min et x_max
float x_min_g = std::numeric_limits<float>::max();
float x_min_d = std::numeric_limits<float>::max();


std::pair< float, float> conversion(int x, int y, int h, int w, std::vector<std::vector<float>> depth ) {

    // V�rifier que les indices sont valides
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > depth[0].size() || y + h > depth.size()) {
        // G�rer les indices invalides ici (par exemple, lancer une exception)
        throw std::invalid_argument("Indices de d�coupe invalides");
    }
    // D�finir la matrice pour la partie extraite
    Matrix partie;
    // Parcourir la partie de la matrice sp�cifi�e par les indices
    for (int i = y; i < y + h; ++i) {
        // Cr�er une ligne pour la partie extraite
        std::vector<float> ligne(depth[i].begin() + x, depth[i].begin() + x + w);
        // Ajouter la ligne � la partie extraite
        partie.push_back(ligne);
    }

    // Parcourir les 10 premi�res colonnes pour x_min_g
    for (int i = y; i < y + h; ++i) {
        for (int j = x; j < x + 4 ; ++j) { // Limiter � 10 premi�res colonnes
            // Mettre � jour x_min si la valeur est inf�rieure
            if (partie[i][j] < x_min_g) {
                x_min_g = partie[i][j];
            }
        }
    }

    // Parcourir les 10 derni�res colonnes pour x_min_d
    for (int i = y; i < y + h; ++i) {
        for (int j = x + w - 4; j < x + w    ; ++j) { // Limiter aux 10 derni�res colonnes
            // Mettre � jour x_max si la valeur est sup�rieure
            if (partie[i][j] < x_min_d) {
                x_min_d = partie[i][j];
            }
        }
    }
    return std::make_pair(x_min_g, x_min_d);
}

// Fonction pour g�n�rer une valeur al�atoire entre min et max
float generateRandomFloat(float min, float max) {
    // Initialiser un g�n�rateur de nombres al�atoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    // G�n�rer un nombre al�atoire entre min et max
    return dis(gen);
}


int main()

{
    // Exemple d'utilisation
    std::vector<std::vector<float>> depth(10, std::vector<float>(10));
    // Remplissage de la matrice avec des valeurs al�atoires
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            depth[i][j] = generateRandomFloat(0.0f, 100.0f); // Valeurs al�atoires entre 0 et 100
        }
    }

    // Affichage de la matrice
    std::cout << "Matrice depth avec des valeurs al�atoires :" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << depth[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int x = 0;
    int y = 0;
    int h = 8;
    int w = 8;

    std::pair<float, float> result = conversion(x, y, h, w, depth);

    std::cout << "Valeur minimale (x_min) : " << result.first << std::endl;
    std::cout << "Valeur maximale (x_max) : " << result.second << std::endl;

    return 0;
}