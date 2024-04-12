#include <iostream>
#include <vector>
#include <cmath>    // pour la fonction std::sqrt
#include <set>      // pour std::set

using namespace std;

// Définition de la structure Rectangle
struct Rectangle {
    float x;          // Coordonnée x du coin supérieur gauche
    float y;          // Coordonnée y du coin supérieur gauche
    float width;      // Largeur du rectangle
    float height;     // Hauteur du rectangle
};

Rectangle get_bounding_rectangle(const std::vector<Rectangle>& rectangles) {
    if (rectangles.empty()) {
        // Retourner un rectangle vide si la liste est vide
        return { 0, 0, 0, 0 };
    }

    float min_x = rectangles[0].x;
    float min_y = rectangles[0].y;
    float max_x = rectangles[0].x + rectangles[0].width;
    float max_y = rectangles[0].y + rectangles[0].height;

    // Parcourir tous les rectangles pour trouver les coordonnées maximales et minimales
    for (const auto& rect : rectangles) {
        min_x = std::min(min_x, rect.x);
        min_y = std::min(min_y, rect.y);
        max_x = std::max(max_x, rect.x + rect.width);
        max_y = std::max(max_y, rect.y + rect.height);
    }

    // Calculer la largeur et la hauteur du rectangle englobant
    float width = max_x - min_x;
    float height = max_y - min_y;

    // Retourner le rectangle englobant
    return { min_x, min_y, width, height };
}


// Fonction de fusion de rectangles
Rectangle merge_rectangles(const std::vector<Rectangle>& rectangles, float dismax, float min_size_threshold) {
    std::set<int> used_rectangles;
    std::vector<Rectangle> merged_rectangles; // Vecteur pour stocker les rectangles fusionnés

    for (int i = 0; i < rectangles.size(); ++i) {
        if (used_rectangles.find(i) != used_rectangles.end()) {
            continue; // Passer à l'itération suivante si le rectangle a déjà été fusionné
        }

        Rectangle merge_candidate = rectangles[i];

        for (int j = i + 1; j < rectangles.size(); ++j) {
            if (used_rectangles.find(j) != used_rectangles.end()) {
                continue; // Passer à l'itération suivante si le rectangle a déjà été fusionné
            }
            Rectangle r1 = rectangles[i];
            Rectangle r2 = rectangles[j];

            float cx1 = r1.x + r1.width / 2;
            float cy1 = r1.y + r1.height / 2;
            float cx2 = r2.x + r2.width / 2;
            float cy2 = r2.y + r2.height / 2;

            float dist = std::sqrt((cx1 - cx2) * (cx1 - cx2) + (cy1 - cy2) * (cy1 - cy2));

            // Vérifier si les deux rectangles sont suffisamment grands et si la distance est dans le seuil
            if (r1.width >= min_size_threshold && r1.height >= min_size_threshold &&
                r2.width >= min_size_threshold && r2.height >= min_size_threshold && dist <= dismax) {
                float x1 = std::min(r1.x, r2.x);
                float y1 = std::min(r1.y, r2.y);
                float x2 = std::max(r1.x + r1.width, r2.x + r2.width);
                float y2 = std::max(r1.y + r1.height, r2.y + r2.height);
                merge_candidate = { x1, y1, x2 - x1, y2 - y1 };
                used_rectangles.insert(j);
            }
        }
        merged_rectangles.push_back(merge_candidate);
        used_rectangles.insert(i);
    }

    // Obtenir le rectangle englobant à partir des rectangles fusionnés
    return get_bounding_rectangle(merged_rectangles);
}

int main() {
    // Exemple d'utilisation
    std::vector<Rectangle> rectangles = {
        {100, 100, 200, 200}, // Rectangle 1
        {150, 150, 250, 250}  // Rectangle 2
    };

    float dismax = 100.0f;             // Distance maximale pour la fusion
    float min_size_threshold = 10.0f; // Seuil de taille minimale

    Rectangle merged_rectangle = merge_rectangles(rectangles, dismax, min_size_threshold);

    // Affichage du rectangle fusionné
    std::cout << "Rectangle fusionné: x=" << merged_rectangle.x << ", y=" << merged_rectangle.y << ", width=" << merged_rectangle.width << ", height=" << merged_rectangle.height << std::endl;

    return 0;
}
