$fn = 60;

prumer = 66;
vyska = 115;
stena = 3;

rotate([0, 0, 0])
{
    difference()
    {
    cylinder(d = prumer, h = vyska);
    translate([0, 0, 1.5]) cylinder(d = prumer - 2, h = vyska);
    }
}