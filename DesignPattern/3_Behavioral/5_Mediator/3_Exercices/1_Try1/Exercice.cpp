#include <iostream>
#include <vector>

struct IParticipant
{
    virtual void increase(int value) = 0;
};

struct Mediator
{
    std::vector<IParticipant*> participants;
};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator& mediator) : mediator(mediator)
    {
        mediator.participants.push_back(this);
    }

    void say(int value)
    {
        for (auto participant : mediator.participants)
        {
            if (participant != this)
            {
                participant->increase(value);
            }
        }
    }

    void increase(int value) override
    {
        Participant::value += value;
    }
};
