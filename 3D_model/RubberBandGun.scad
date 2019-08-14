// Science-Fiction Rubber Band Gun - 2019-08-13
// Mark Olson
// https://github.com/Mark-MDO47/RubberBandGun

// Crude representation of physical layout

// all measurements in millimeters (mm)

Bat18650Btn_Len   = 70; // slightly more than 650
Bat18650Btn_Rad   = 18;
Barrel_Rad        = 30;

LED_Small_Dim     = 2;  // thickness of ring
LED_Large_Dim     = 15; // width of ring

LED_Num           = 4;
LED_ORadius_Delta = 20;
LED_ORadius_Min   = 50;
LED_ORadius_Max   = 110;

LED_Handle_offset = 15;

Handle_Len        = 55;
Handle_Height     = 120;
Handle_Width      = 2*Barrel_Rad/3;
Barrel_Len        = 2*Bat18650Btn_Len + Handle_Len + 50;


COLOR_Barrel = "aqua";
COLOR_LED = "red";
COLOR_Handle = "brown";
// COLOR_ = "blue";
// COLOR_ = "purple";

module led_ring(torus_outer_radius) {
    
    color(COLOR_LED) rotate_extrude($fn=128) {
       translate ([torus_outer_radius, 0]) square([LED_Large_Dim,2*LED_Small_Dim]); 
    }

}

led_space = (Barrel_Len-Handle_Len-LED_Handle_offset) / (LED_Num-1);

translate([0, 0, -(LED_Handle_offset+Handle_Len-LED_Small_Dim/2)]) {
    for (idx = [0: LED_Num-1]) {
        translate ([0, 0, -idx*led_space]) led_ring(LED_ORadius_Min + idx*LED_ORadius_Delta);
    }
}
color(COLOR_Barrel) translate([0,0,-Barrel_Len]) cylinder(Barrel_Len, r=Barrel_Rad, $fn=128);
color(COLOR_Handle) translate([0,-Handle_Width/2,-(Handle_Len+0.01)]) cube([Handle_Height,Handle_Width,Handle_Len]);