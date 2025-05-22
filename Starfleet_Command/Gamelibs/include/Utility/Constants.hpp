#ifndef STARFLEET_COMMAND_CONSTANTS_HPP
#define STARFLEET_COMMAND_CONSTANTS_HPP

struct Constants
{
    static constexpr float WINDOW_WIDTH  = 1280.F;
    static constexpr float WINDOW_HEIGHT = 720.F;

    static constexpr float LEVEL_WIDTH   = 4096.F; // x size of background image
    static constexpr float LEVEL_HEIGHT  = 2304.F; // y size of background image  (scaled up from 1280x720)

    struct Minimap
    {
        static constexpr float VIEWPORT_SCALE_FACTOR = 1.25F;

        static constexpr float VIEWPORT_WIDTH  = 0.5F / VIEWPORT_SCALE_FACTOR;
        static constexpr float VIEWPORT_HEIGHT = 0.166F / VIEWPORT_SCALE_FACTOR;

        static constexpr float VIEWPORT_LEFT   = 0.5F - VIEWPORT_WIDTH/2.0F;
        static constexpr float VIEWPORT_TOP    = 0.075F - VIEWPORT_HEIGHT/2.0F;
    };
};

#endif //STARFLEET_COMMAND_CONSTANTS_HPP
