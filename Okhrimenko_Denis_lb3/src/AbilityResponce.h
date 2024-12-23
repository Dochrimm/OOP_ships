#ifndef ABILITY_RESPONCE_H 
#define ABILITY_RESPONCE_H

#include <iostream>

class AbilityResponce
{
public:
    enum class DoubleDamageStatus
    {
        activated,
        disable
    };
    enum class ScannerStatus
    {
        detected,
        clear
    };
    enum class Ability
    {
        DoubleDamage,
        Scanner,
        Bombardment
    };

private:
    DoubleDamageStatus double_damage_status;
    ScannerStatus scanner_status;
    Ability last_ability_used;

public:
    AbilityResponce();
    void doubleDamageActivated();
    void disableDoubleDamage();
    void scannerReturnTrue();
    void scannerReturnFalse();
    void setLastAbility(Ability ability);
    DoubleDamageStatus getDoubleDamageStatus() const;
    void getAbilityResult() const;
};

#endif