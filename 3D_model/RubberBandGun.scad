// Science-Fiction Rubber Band Gun - 2019-08-13
// Mark Olson
// https://github.com/Mark-MDO47/RubberBandGun

// Crude representation of physical layout

// all measurements in millimeters (mm)

Bat18650Btn_Len   = 70; // slightly more than 650 with the button
Bat18650Btn_Rad   = 9;  // diameter is 18
Bat18650Btn_Num   = 2;  // how many batteries in gun; min is 2 to get > 6 Volts

Barrel_ClothesPin_Trigger = 50; // zero if ClothesPin is not trigger
Barrel_Len_extra  = 50; // wood for barrel at end of batteries
Barrel_Rad_extra  = 8;  // wood for barrel around batteries
Barrel_Rad        = Bat18650Btn_Rad+Barrel_Rad_extra;

LED_Small_Dim     = 2;  // thickness of ring
LED_Large_Dim     = 15; // width of ring

LED_Num           = 4;
LED_ORadius_Delta = 20/2;
LED_ORadius_Min   = 50/2;
LED_ORadius_Max   = 110/2;

LED_Handle_offset = 15;

Handle_Len        = 55;
Handle_Height     = 120;
Handle_Width      = 2*Barrel_Rad/3;
Barrel_Len        = Bat18650Btn_Num*Bat18650Btn_Len + Handle_Len + Barrel_Len_extra + Barrel_ClothesPin_Trigger;

ClothesPin_Mmbr_Height = Handle_Height/6*5;
ClothesPin_Mmbr_Thick = 4;
ClothesPin_Mmbr_Width = 12;


COLOR_Barrel = "aqua";
COLOR_LED = "red";
COLOR_Handle = "brown";
// COLOR_ = "blue";
// COLOR_ = "purple";

// draw one member of wooden clothespin
module clothespin_mmbr() {
    linear_extrude(height = ClothesPin_Mmbr_Height, center = true, convexity = 10, scale=1) square([ClothesPin_Mmbr_Thick,ClothesPin_Mmbr_Width]);
}

// draw clothespin
module clothespin() {
    clothespin_mmbr();
    rotate([0,-5,180]) translate([ClothesPin_Mmbr_Thick/2,-ClothesPin_Mmbr_Width,0]) clothespin_mmbr();
    
}

// draw a single LED ring
module led_ring(torus_outer_radius) {
    
    color(COLOR_LED) rotate_extrude($fn=128) {
       translate ([torus_outer_radius, 0]) square([LED_Large_Dim,2*LED_Small_Dim]); 
    }

}

// calculate spacing for LED rings
led_first = Handle_Len + Barrel_ClothesPin_Trigger+ LED_Handle_offset;
led_space = (Barrel_Len - led_first) / (LED_Num-1);

// draw the LED rings
for (idx = [0: LED_Num-1]) {
    translate ([0, 0, -led_first-(LED_Small_Dim/2)-idx*led_space]) led_ring(LED_ORadius_Min + idx*LED_ORadius_Delta);
}

// draw the barrel
color(COLOR_Barrel) translate([0,0,-Barrel_Len]) cylinder(Barrel_Len, r=Barrel_Rad, $fn=128);

// draw the handle
color(COLOR_Handle) translate([0,-Handle_Width/2,-(Handle_Len+0.01)]) cube([Handle_Height,Handle_Width,Handle_Len]);

// draw the clothespin
translate([ClothesPin_Mmbr_Height/2+Barrel_Rad,-ClothesPin_Mmbr_Width/2,-Handle_Len-ClothesPin_Mmbr_Thick]) rotate ([0,-90,0]) clothespin();
