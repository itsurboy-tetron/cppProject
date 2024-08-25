#include <SFML/Graphics.hpp>
#include <vector>

const int BOARD_SIZE = 5;
const int CELL_SIZE = 100;

enum Piece { EMPTY, TIGER, GOAT };

class Baghchal {
private:
    std::vector<std::vector<Piece>> board;
    int goatsPlaced;
    int goatsCaptured;

public:
    Baghchal() : board(BOARD_SIZE, std::vector<Piece>(BOARD_SIZE, EMPTY)), goatsPlaced(0), goatsCaptured(0) {
        board[0][0] = TIGER;
        board[0][4] = TIGER;
        board[4][0] = TIGER;
        board[4][4] = TIGER;
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);
                cell.setFillColor(sf::Color::White);
                window.draw(cell);

                sf::CircleShape piece(CELL_SIZE / 2 - 10);
                piece.setPosition(i * CELL_SIZE + 10, j * CELL_SIZE + 10);
                if (board[i][j] == TIGER) {
                    piece.setFillColor(sf::Color::Yellow);
                    window.draw(piece);
                } else if (board[i][j] == GOAT) {
                    piece.setFillColor(sf::Color::Green);
                    window.draw(piece);
                }
            }
        }
    }

    bool placeGoat(int x, int y) {
        if (board[x][y] == EMPTY && goatsPlaced < 20) {
            board[x][y] = GOAT;
            goatsPlaced++;
            return true;
        }
        return false;
    }

    bool moveTiger(int fromX, int fromY, int toX, int toY) {
        if (board[fromX][fromY] == TIGER && board[toX][toY] == EMPTY) {
            board[fromX][fromY] = EMPTY;
            board[toX][toY] = TIGER;
            return true;
        }
        return false;
    }

    bool captureGoat(int tigerX, int tigerY, int goatX, int goatY, int emptyX, int emptyY) {
        if (board[tigerX][tigerY] == TIGER && board[goatX][goatY] == GOAT && board[emptyX][emptyY] == EMPTY) {
            board[tigerX][tigerY] = EMPTY;
            board[goatX][goatY] = EMPTY;
            board[emptyX][emptyY] = TIGER;
            goatsCaptured++;
            return true;
        }
        return false;
    }

    bool isGameOver() {
        return goatsCaptured >= 5;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "Baghchal Game");

    Baghchal game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;
                game.placeGoat(x, y);
            }
        }

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}
