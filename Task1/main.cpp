#include <iostream>
#include <string>

class GameEntity {
public:
    std::string Name;
    int Health;
    bool CanTalk;
    bool CanAttack;
    bool CanMove;
    bool HasHealth; // Флаг для наличия здоровья (для Loader)
    bool HasName;   // Флаг для наличия имени (для Zombie)

    GameEntity(const std::string& name, int health, bool canTalk, bool canAttack, bool canMove, bool hasHealth, bool hasName)
        : CanTalk(canTalk), CanAttack(canAttack), CanMove(canMove), HasHealth(hasHealth), HasName(hasName) {
        if (hasName) {
            Name = name;
        } else {
            Name = ""; // Пустая строка для Zombie
        }
        if (hasHealth) {
            Health = health;
        } else {
            Health = 0;
        }
    }

    void Move() {
        if (CanMove) {
            std::string entityIdentifier = HasName ? Name : "Zombie";
            std::cout << entityIdentifier << " is moving." << std::endl;
        } else {
            std::cout << "This entity can't move." << std::endl;
        }
    }

    void Attack() {
        if (CanAttack) {
            std::string entityIdentifier = HasName ? Name : "Zombie";
            std::cout << entityIdentifier << " attacks for 10 damage!" << std::endl;
        } else {
            std::cout << "This entity can't attack." << std::endl;
        }
    }

    void Talk(const std::string& message) {
        if (CanTalk) {
            std::string entityIdentifier = HasName ? Name : "Zombie";
            std::cout << entityIdentifier << " says: " << message << std::endl;
        } else {
            std::cout << "This entity can't talk." << std::endl;
        }
    }

    void TakeDamage(int damage) {
        if (HasHealth) {
            Health -= damage;
            std::string entityIdentifier = HasName ? Name : "Zombie";
            std::cout << entityIdentifier << " takes " << damage << " damage. Remaining health: " << Health << std::endl;
            if (Health <= 0) {
                std::cout << entityIdentifier << " has died." << std::endl;
            }
        } else {
            std::cout << "This entity has no health to damage." << std::endl;
        }
    }
};

int main() {
    // Создание Player
    GameEntity player("Hero", 100, true, true, true, true, true);
    std::cout << "Player actions:" << std::endl;
    player.Move();
    player.Attack();
    player.Talk("Hello, world!");
    player.TakeDamage(20);
    std::cout << std::endl;

    // Создание Loader
    GameEntity loader("Bob", 0, true, false, true, false, true);
    std::cout << "Loader actions:" << std::endl;
    loader.Move();
    loader.Attack();
    loader.Talk("Loading cargo...");
    loader.TakeDamage(10);
    std::cout << std::endl;

    // Создание Zombie
    GameEntity zombie("", 50, false, true, true, true, false);
    std::cout << "Zombie actions:" << std::endl;
    zombie.Move();
    zombie.Attack();
    zombie.Talk("Brains...");
    zombie.TakeDamage(30);
    std::cout << std::endl;

    return 0;
}