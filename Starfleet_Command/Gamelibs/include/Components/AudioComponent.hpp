#ifndef STARFLEET_COMMAND_AUDIOCOMPONENT_HPP
#define STARFLEET_COMMAND_AUDIOCOMPONENT_HPP

class AudioComponent
{
public:
    AudioComponent() = default;
    ~AudioComponent() = default;

    void PlayAudio();
    void StopAudio();

private:
};

#endif //STARFLEET_COMMAND_AUDIOCOMPONENT_HPP
