include<Values.scad>

$fn = 20;

module rozek()
{
    cube([rozek_rozm, rozek_rozm, rozek_rozm]);
}

module obal()
{
    difference()
    {
        cube([ven_sirka, ven_delka, ven_vyska]);
        translate ([(ven_sirka - vnit_sirka) / 2, (ven_delka - vnit_delka) / 2, ven_vyska - vnit_vyska]) cube([vnit_sirka, vnit_delka, vnit_vyska]);
    }
}

module otvory()
{
    color("red") translate([vzdal_usb_x, 0, vzdal_usb_z]) cube([usb_sirka, (ven_delka - vnit_delka) / 2, usb_vyska]);
    color("red") rotate([270, 0, 0]) translate([vzdal_antena_x, -vzdal_antena_z, 0]) cylinder(d = antena_prumer, h = (ven_delka - vnit_delka) / 2);
}


difference()
{
    obal();
    otvory();
}

translate([100, 0, 0]) rozek();
