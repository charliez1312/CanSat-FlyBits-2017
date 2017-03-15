$fn = 20;

delka_ven = 114;
sirka_ven = 62;
vyska_ven = 36;

delka_vnit = 110;
sirka_vnit = 58;
vyska_vnit = 33;

module main()
{
    difference()
    {
        cube([delka_ven, sirka_ven, vyska_ven]);
        translate ([(delka_ven - delka_vnit) / 2, (sirka_ven - sirka_vnit) / 2, vyska_ven - vyska_vnit]) cube([delka_vnit, sirka_vnit, vyska_vnit]);
    }
}

main();