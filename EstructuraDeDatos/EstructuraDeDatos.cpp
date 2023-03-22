#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Esta es la estructura básica de un objeto del juego
struct GameObject {
    std::string name;
    int value;
};

// Esta es la estructura de los datos del jugador que se guardarán
struct PlayerData {
    std::string name;
    int health;
    int score;
    GameObject weapon;
};

// creación de un nuevo archivo de guardado
void createSaveFile(const std::string& filename) {
    std::ofstream file(filename);
    json saveData;
    saveData["player"] = {
        {"name", "Player 1"},
        {"health", 100},
        {"score", 0},
        {"weapon", {
            {"name", "Pistol"},
            {"value", 10}
        }}
    };
    file << saveData.dump(4); //  archivo con sangría de 4 espacios
    std::cout << "Nuevo archivo de guardado creado: " << filename << std::endl;
}

// carga de un archivo de guardado existente
PlayerData loadSaveFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Archivo de guardado no encontrado. Creando nuevo archivo de guardado." << std::endl;
        createSaveFile(filename);
        return loadSaveFile(filename);
    }
    json saveData;
    file >> saveData;
    PlayerData playerData = {
        saveData["player"]["name"],
        saveData["player"]["health"],
        saveData["player"]["score"],
        { saveData["player"]["weapon"]["name"], saveData["player"]["weapon"]["value"] }
    };
    std::cout << "Archivo de guardado cargado: " << filename << std::endl;
    return playerData;
}

int main() {
    std::string saveFilename = "save.json";
    PlayerData playerData = loadSaveFile(saveFilename);

    
    std::cout << "¡Bienvenido a mi juego!" << std::endl;
    std::cout << "Tu nombre es " << playerData.name << ", tu salud es " << playerData.health << ", y tu puntuación es " << playerData.score << "." << std::endl;
    std::cout << "Tu arma actual es " << playerData.weapon.name << " que tiene un valor de " << playerData.weapon.value << "." << std::endl;

    
    playerData.health -= 20;
    playerData.score += 100;
    playerData.weapon = { "Rifle", 25 };
    std::cout << "¡Has ganado la batalla! Tu salud es ahora " << playerData.health << ", tu puntuación es " << playerData.score << ", y tu nueva arma es " << playerData.weapon.name << "." << std::endl;

    
    std::ofstream file(saveFilename);
    json saveData;
    saveData["player"] = {
    {"name", playerData.name},
    {"health", playerData.health},
    {"score", playerData.score},
    {"weapon", {
        {"name", playerData.weapon.name},
        {"value", playerData.weapon.value}
    }}
    };
    file << saveData.dump(4);
    std::cout << "Guardando archivo de guardado..." << std::endl;

    // Salida del programa
    std::cout << "Gracias por jugar. ¡Hasta la próxima!" << std::endl;
    return 0;
}