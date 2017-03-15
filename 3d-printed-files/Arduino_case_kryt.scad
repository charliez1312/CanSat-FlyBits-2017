use<Write.scad>
include<Values.scad>

$fn = 30;

module kryt()
{
    cube([ven_sirka, ven_delka, kryt_vyska]);
    color("red") rotate([0, 0, 90]) translate([0, 0, 20]) write("FlyBits", h = 20, t = 3);

}

kryt();