$fn = 150;

prumer = 66;
vyska = 115;

rotate([0, 0, 0])
{difference()
{
    cylinder(d = prumer, h = vyska);
    translate([0, 0, 1.5]) cylinder(d = prumer - 10, h = vyska);
}
}