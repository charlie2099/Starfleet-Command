#ifndef STARFLEET_COMMAND_CONSTANTS_HPP
#define STARFLEET_COMMAND_CONSTANTS_HPP

struct Constants
{
    static constexpr float WINDOW_WIDTH  = 1280.F;
    static constexpr float WINDOW_HEIGHT = 720.F;
    
    static constexpr float LEVEL_WIDTH   = 4096.F; // x size of background image
    static constexpr float LEVEL_HEIGHT  = 2304.F; // y size of background image  (scaled up from 1280x720)

    static constexpr float VIEWPORT_WIDTH  = 0.2f;                        // original 0.2f
    static constexpr float VIEWPORT_HEIGHT = 0.2f;                        // original 0.2f
    static constexpr float VIEWPORT_LEFT   = 0.11f - VIEWPORT_WIDTH/2.0F; // original 0.5f - VIEWPORT_WIDTH/2.0f
    static constexpr float VIEWPORT_TOP    = 0.021f;                       // original 0.01f
};

#endif //STARFLEET_COMMAND_CONSTANTS_HPP
