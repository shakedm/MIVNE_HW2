#ifndef MIVNE_WET2_GLADIATOR_H
#define MIVNE_WET2_GLADIATOR_H

class Gladiator{
private:
    friend class Arena;
    int GladiatorID;
    int Level;
public:
    Gladiator(int ID, int Level);
    int GetID() const;
    int GetLvl() const;

    friend bool operator==(const Gladiator& l, const Gladiator& r);
    friend bool operator<(const Gladiator& l, const Gladiator& r);
    friend bool operator>(const Gladiator& l, const Gladiator& r);
    friend bool operator!=(const Gladiator& l, const Gladiator& r);
};

#endif //MIVNE_WET2_GLADIATOR_H
