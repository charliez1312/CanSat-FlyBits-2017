use<Write.scad>
include<Arduino_case_values.scad>

$fn = 300;

module kryt()
{
    difference()
    {
        union()
        {
        cube([ven_sirka, ven_delka, kryt_vyska]);
        color("red") rotate([0, 0, 90]) translate([17, -39, kryt_vyska]) write("Fly", h = 17, t = vyska_pisma);
        color("red") rotate([0, 0, 90]) translate([56, -39, kryt_vyska]) write("Bits", h = 17, t = vyska_pisma);
        color("red") rotate([0, 0, 90]) translate([44, -15, kryt_vyska]) write("CanSat", h = 7, t = vyska_pisma);
        }
        union()
        {
        translate([17, 5, 0]) cylinder(d = rozek_dira, h = kryt_vyska);
        translate([57, 5, 0]) cylinder(d = rozek_dira, h = kryt_vyska);
        translate([57, 111, 0]) cylinder(d = rozek_dira, h = kryt_vyska);
        translate([5, 111, 0]) cylinder(d = rozek_dira, h = kryt_vyska);
            
        translate([48, 48, 0]) cube(ledka_rozmer);
        translate([48, 63, 0]) cube(ledka_rozmer);
        }
        
    }
}

kryt();
