use<Write.scad>

$fn = 20;

ven_delka = 114;
ven_sirka = 62;
ven_vyska = 36;

vnit_delka = 110;
vnit_sirka = 58;
vnit_vyska = 33;

usb_sirka = 12;
usb_vyska = 12; //?
vzdal_usb_z = (ven_vyska - vnit_vyska) + 5; //?
vzdal_usb_x = (ven_sirka - vnit_sirka) / 2 + 9;

antena_prumer = 13;
vzdal_antena_x = 38;
vzdal_antena_z = 25; //?

rozek_rozm = 6;

kryt_vyska = 3;

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


//difference()
//{
//    obal();
//    otvory();
//}

//translate([100, 0, 0]) rozek();

module kryt()
{
    cube([ven_sirka, ven_delka, kryt_vyska]);
    color("red") rotate([0, 0, 90]) translate([0, 0, 20]) write("FlyBits", h = 20, t = 3);


}

kryt();