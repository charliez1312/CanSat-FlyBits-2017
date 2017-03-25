$fn = 200;

prumer = 65;
vyska = 115;
stena = 2.5;

sirka_deska_soucastky = 12;
vyska_deska_soucastky = 50;

vnejsi_prumer_zavit = prumer - 2 * stena;
vnitrni_prumer_zavit = vnejsi_prumer_zavit - 5;

module cansat()
{
    difference()
    {
    cylinder(d = prumer, h = vyska);
    translate([0, 0, stena]) cylinder(d = prumer - 2 * stena, h = vyska);
    }
}

module deska_soucastky()
{
    translate([-prumer/2 - stena, -sirka_deska_soucastky/2, 25]) cube([stena*3, sirka_deska_soucastky, vyska_deska_soucastky]);
}

module drzak_desky()
{
    module drzak_desky_hlavni()
    {
        translate([-4, 0 , 0]) cube([3, 4, vyska - stena]);
        translate([1, 0, 0]) cube([3, 4, vyska - stena]);
    }
    translate([0, 26, 0]) drzak_desky_hlavni();
    translate([0, -30, 0]) drzak_desky_hlavni();
}

module zavit()
{
    translate([0, 0, 106.5]) difference()
    {
        difference()
        {
            cylinder(d = vnejsi_prumer_zavit, h = 8.5);
            cylinder(d = vnitrni_prumer_zavit, h = 8.5);
        }
        union()
        {
            translate([-1, 27, 0]) cube([2, 3, 15]);
            translate([-1, -30, 0]) cube([2, 3, 15]);
        }
}
}


difference()
{
    union()
    {
        cansat();
        drzak_desky();
        zavit();
    }
    deska_soucastky();
}
