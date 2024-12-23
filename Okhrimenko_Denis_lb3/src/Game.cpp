#include "Game.h"


Game::Game() {
    initializeGame();
    std::cout << "Добро пожаловать в игру!\n";
    std::cout << "Выберите действие:\n";
    std::cout << "1. Начать новую игру\n";
    std::cout << "2. Загрузить сохраненную игру\n";
    int choice = CoordReader::readCoord("Введите номер действия: ");
    switch (choice) {
        case 1:
            newGame();
            break;
        case 2:
            if (gameState->loadFromFile()) { // Пробуем загрузить игру из файла
                isLoaded = true;
                std::cout << YELLOW << "Игра загружена из файла." << RESET << '\n';
            } else {
                std::cout << YELLOW << "Не удалось загрузить игру. Начните новую игру." << RESET << '\n';
            }
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << '\n';
            break;
    }
}

Game::~Game() {
    cleanUp();
}

void Game::cleanUp() {
    delete myship;
    delete opponentsship;
    delete my_map;
    delete opponents_map;
    delete skillManager;
    delete responce;
    delete humanPlayer;
    delete computerPlayer;
    delete coordHolder;
    delete gameState;
}

void Game::initializeGame() {
    isRunningGame = false;
    isLoaded = false; // Изначально игра не загружена
    roundNumber = 1;
    std::vector<int> leng{1, 1};
    myship = new ShipManager(2, leng);
    opponentsship = new ShipManager(2, leng);
    responce = new AbilityResponce();
    coordHolder = new CoordHolder();

    my_map = new Map(10, 10, myship);
    opponents_map = new Map(10, 10, opponentsship);
    skillManager = new AbilityManager(*opponents_map, *coordHolder);

    gameState = new GameState(my_map, opponents_map, myship, opponentsship, skillManager, coordHolder);

    humanPlayer = new HumanPlayer(my_map, myship, gameState);
    computerPlayer = new ComputerPlayer(opponents_map, opponentsship, gameState);
}

void Game::gameStart() {
    std::cout << YELLOW << "Игра началась!" << RESET << '\n';
    isRunningGame = true;
    saveWithArrangement();

    if (!isLoaded) { // Если игра не была загружена, размещаем корабли противника
        computerPlayer->placeShips();
    }

    Round();
}

void Game::gameOver() {
    isRunningGame = false;
    std::cout << YELLOW << "Игра окончена!" << RESET << '\n';
}

void Game::Round() {
    while (isRunningGame) {
        std::cout << YELLOW << "Раунд " << roundNumber << " начался!" << RESET << '\n';
        while (isRunningGame) {
            humanPlayer->makeMove(opponents_map, responce, skillManager);
            if (computerPlayer->allShipsDestroyed()) {
                std::cout << BLUE << "Вы победили в раунде " << RESET << roundNumber << "!" << '\n';
                nextRound();
                return;
            }
            computerPlayer->makeMove(my_map, responce, skillManager);
            if (humanPlayer->allShipsDestroyed()) {
                std::cout << BLUE << "Вы проиграли раунд " << RESET << roundNumber << "!" << '\n';
                newGame();
                return;
            }
        }
    }
}

void Game::nextRound() {
    roundNumber++;

    opponentsship->restoreShips();
    opponents_map->clear();

    computerPlayer->placeShips(); // Размещаем корабли противника для нового раунда

    Round();
}

void Game::newGame() {
    std::cout << "Начать новую игру? (1 - Да, 0 - Нет): ";
    int choice = CoordReader::readCoord("");

    if (choice == 1) {
        cleanUp(); // Освобождаем память предыдущей игры
        initializeGame(); // Инициализируем новую игру

        gameStart();

    } if(choice == 0) {
        gameOver(); // Завершаем игру
    }
}

void Game::saveWithArrangement() {
    printMaps();
    std::cout << "Выберите действие:\n1. поставить корабль\n2. Сохранить игру\n3. Загрузить игру\n4. продолжить игру\n";
    int choice = CoordReader::readCoord("Введите номер действия: ");

    switch (choice) {
        case 1:
            humanPlayer->placeShips();
            saveWithArrangement();
            break;
        case 2:
            if (gameState->saveToFile()) { // Сохраняем игру в файл
                std::cout << "Игра сохранена." << '\n';
            }
            saveWithArrangement();
            break;
        case 3:
            if (gameState->loadFromFile()) { // Загружаем игру из файла
                isLoaded = true; // Устанавливаем флаг, что игра загружена
                std::cout << "Игра загружена." << '\n';
            }
            saveWithArrangement();
            break;
        case 4:
            return; // Продолжаем игру, если она загружена
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << '\n';
            saveWithArrangement();
            break;
    }
}

void Game::printMaps() {
    std::cout << "Ваша карта:" << '\n';
    my_map->printMap(true);

    std::cout << '\n' << "Карта противника:" << '\n';
    opponents_map->printMap(false);
}