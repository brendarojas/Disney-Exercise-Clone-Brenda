#define RESOURCES_DIR "resources/"
#define SPLASH_IMG "disneylogo.jpg"
#define FONT_FILE RESOURCES_DIR "avenir-roman.ttf"

// coordinates

#define LEFT_MARGIN 50
#define TOP_MARGIN 30

#define RIGHT_MARGIN 50
#define BOT_MARGIN 50

#define THUMB_WIDTH 250
#define THUMB_HEIGHT 140

#define THUMB_X_SPACING 20
#define THUMB_Y_SPACING 50

#define ITEMS_PER_PAGE 5
#define SETS_PER_PAGE 4

#define TEXT_HEIGHT 33

// define the window size based on the quantity of items to be displayed per page
#define SCREEN_WIDTH \
    (LEFT_MARGIN + (THUMB_WIDTH * ITEMS_PER_PAGE) + (THUMB_X_SPACING * (ITEMS_PER_PAGE - 1)) + RIGHT_MARGIN)  // 1430
#define SCREEN_HEIGHT                                                                                        \
    (TOP_MARGIN + ((THUMB_HEIGHT + TEXT_HEIGHT) * SETS_PER_PAGE) + (THUMB_Y_SPACING * (SETS_PER_PAGE - 1)) + \
     BOT_MARGIN)  // 900                                                                                      // 800

#define TEXT_X_COORD LEFT_MARGIN
#define Y_SEPARATOR (THUMB_HEIGHT + TEXT_HEIGHT + THUMB_Y_SPACING)
#define TEXT_Y_COORD(set) (TOP_MARGIN + (Y_SEPARATOR * set))

#define X_SEPARATOR (THUMB_WIDTH + THUMB_X_SPACING)
#define ITEM_X_COORD(item) (LEFT_MARGIN + (X_SEPARATOR * item))
#define ITEM_Y_COORD(set) (TOP_MARGIN + 40 + (Y_SEPARATOR * set))