$fn = 30;

prumer = 65;
vyska = 114;
stena = 2.5;

sirka_cidla = 12;
vyska_cidla = 50;

module cansat()
{
    difference()
    {
    cylinder(d = prumer, h = vyska);
    translate([0, 0, stena]) cylinder(d = prumer - 2 * stena, h = vyska);
    }
}

module otvory()
{
    color("red") translate([-prumer/2 - stena, -sirka_cidla/2, 25]) cube([stena*3, sirka_cidla, vyska_cidla]);
}

module drzak_desky()
{
    translate() cube(4);
    translate() cube(5);
}


difference()
{
    union()
    {
        cansat();
        translate([50, 0, 0]) drzak_desky();
    }
    otvory();
}