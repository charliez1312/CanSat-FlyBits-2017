include<Arduino_case_values.scad>
use<Write.scad>

$fn = 300;

module rozek()
{
    difference()
    {
        union()
        {
            cube([rozek_rozm, rozek_rozm, rozek_rozm]);
            translate([1.1, rozek_rozm, -0.55]) rotate([90, -7, 0]) cylinder(d = 10, h = rozek_rozm, $fn=3);
        }
        color("red") translate([-5, 0, -5.2]) cube([5, rozek_rozm, 12.3]);
        translate([3, 3, -3]) cylinder(d = rozek_dira, h = 12);
    }
}

module nastavec()
{
    difference()
    {
        cylinder(d = nastavec_prumer, h = nastavec_vyska);
        cylinder(d = nastavec_prumer_dira, h = nastavec_vyska);
    }
}

module obal()
{
    difference()
    {
        cube([ven_sirka, ven_delka, ven_vyska]);
        translate ([(ven_sirka - vnit_sirka) / 2, (ven_delka - vnit_delka) / 2, ven_vyska - vnit_vyska]) cube([vnit_sirka, vnit_delka, vnit_vyska]);
    }
    translate([20, 2, 32]) rotate([0, 0, 90]) rozek();
    translate([60, 2, 32]) rotate([0, 0, 90]) rozek();
    translate([2, 114, 32]) rotate([0, 0, 270]) rozek();
    translate([54, 114, 32]) rotate([0, 0, 270]) rozek();
    
    translate([4, 17, nastavec_vyska]) nastavec();
    translate([4, 92, nastavec_vyska]) nastavec();
    translate([52, 16, nastavec_vyska]) nastavec();
    translate([52, 99, nastavec_vyska]) nastavec();
}

module otvory()
{
    translate([vzdal_usb_x, 0, vzdal_usb_z]) cube([usb_sirka, (ven_delka - vnit_delka) / 2, usb_vyska]);
    rotate([270, 0, 0]) translate([vzdal_antena_x, -vzdal_antena_z, 0]) cylinder(d = antena_prumer, h = (ven_delka - vnit_delka) / 2);
    translate([vzdal_napajeni_x, 0, vzdal_napajeni_z]) cube([napajeni_sirka, (ven_delka - vnit_delka) / 2, napajeni_vyska]);
}


difference()
{
    obal();
    otvory();
}
