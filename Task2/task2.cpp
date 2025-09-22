#include <iostream>
#include <string>

// Базовый класс для всех сущностей (уровень 1)
class BaseEntity {
public:
    virtual void Move() {
        std::cout << "Entity is moving." << std::endl;
    }

    virtual ~BaseEntity() {} // Виртуальный деструктор для правильного наследования
};

// Класс для сущностей с именем и говорением (уровень 2)
class NamedEntity : virtual public BaseEntity {
protected:
    std::string Name;

public:
    NamedEntity(const std::string& name) : Name(name) {}

    virtual void Talk(const std::string& message) {
        std::cout << Name << " says: " << message << std::endl;
    }

    std::string GetName() const {
        return Name;
    }
};

// Класс для сущностей со здоровьем, атакой и уроном (уровень 2)
class HealthEntity : virtual public BaseEntity {
protected:
    int Health;

public:
    HealthEntity(int health) : Health(health) {}

    virtual void Attack() {
        std::cout << "Entity attacks for 10 damage!" << std::endl;
    }

    virtual void TakeDamage(int damage) {
        Health -= damage;
        std::cout << "Entity takes " << damage << " damage. Remaining health: " << Health << std::endl;
        if (Health <= 0) {
            std::cout << "Entity has died." << std::endl;
        }
    }
};

// Игрок: Наследует от NamedEntity и HealthEntity (уровень 3, множественное наследование)
class Player : public NamedEntity, public HealthEntity {
public:
    Player(const std::string& name, int health)
        : BaseEntity(), NamedEntity(name), HealthEntity(health) {}

    // Переопределяем Move, Attack, Talk, TakeDamage для кастомизации
    void Move() override {
        std::cout << Name << " is moving." << std::endl;
    }

    void Attack() override {
        std::cout << Name << " attacks for 10 damage!" << std::endl;
    }

    void TakeDamage(int damage) override {
        Health -= damage;
        std::cout << Name << " takes " << damage << " damage. Remaining health: " << Health << std::endl;
        if (Health <= 0) {
            std::cout << Name << " has died." << std::endl;
        }
    }
};

// Грузчик: Наследует только от NamedEntity (нет здоровья и атаки) (уровень 3)
class Loader : public NamedEntity {
public:
    Loader(const std::string& name) : NamedEntity(name) {}

    void Move() override {
        std::cout << Name << " is moving." << std::endl;
    }

    // Нет атаки — если вызовем, можно бросить исключение или вывести сообщение
    void Attack() {
        std::cout << "This entity can't attack." << std::endl;
    }

    void TakeDamage(int damage) {
        std::cout << "This entity has no health to damage." << std::endl;
    }
};

// Зомби: Наследует только от HealthEntity (нет имени и говорения) (уровень 3)
class Zombie : public HealthEntity {
public:
    Zombie(int health) : HealthEntity(health) {}

    void Move() override {
        std::cout << "Zombie is moving." << std::endl;
    }

    void Attack() override {
        std::cout << "Zombie attacks for 10 damage!" << std::endl;
    }

    void TakeDamage(int damage) override {
        Health -= damage;
        std::cout << "Zombie takes " << damage << " damage. Remaining health: " << Health << std::endl;
        if (Health <= 0) {
            std::cout << "Zombie has died." << std::endl;
        }
    }

    // Нет говорения
    void Talk(const std::string& message) {
        std::cout << "This entity can't talk." << std::endl;
    }
};

int main() {
    // Создание Player
    Player player("Hero", 100);
    std::cout << "Player actions:" << std::endl;
    player.Move();
    player.Attack();
    player.Talk("Hello, world!");
    player.TakeDamage(20);
    std::cout << std::endl;

    // Создание Loader
    Loader loader("Bob");
    std::cout << "Loader actions:" << std::endl;
    loader.Move();
    loader.Attack();
    loader.Talk("Loading cargo...");
    loader.TakeDamage(10);
    std::cout << std::endl;

    // Создание Zombie
    Zombie zombie(50);
    std::cout << "Zombie actions:" << std::endl;
    zombie.Move();
    zombie.Attack();
    zombie.Talk("Brains...");
    zombie.TakeDamage(30);
    std::cout << std::endl;

    return 0;
}