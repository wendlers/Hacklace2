/**
 * Simple Hacklace2 Case
 *
 * 2014-11-04
 * Stefan Wendler
 * sw@kaltpost.de
 */

show(0);
// show_exploded(1);
// print_case(1);
// hl2(1);

module show(with_headers)
{
	translate([0, 0, 3+9.5-3])
		hl2(with_headers);
	
	color("green")
		case_lower(with_headers);
}


module show_exploded(with_headers)
{
	translate([0, 0, 35])
 		hl2(with_headers);
	
	color("green")
		case_lower(with_headers);
}

module print_case(with_headers)
{
	case_lower(with_headers);
}

module case_lower(with_headers)
{
	union()
	{
		difference()
		{
			translate([0, 0, 16/2-2])
				cube([48 + 7, 26 + 4, 13], center=true);
	
			translate([0, 0, 16/2])
				cube([47, 26, 13], center=true);
	
			translate([0, 0, 3+9.5-3])
				hl2(with_headers);
			
			translate([0, 0, 11.5])
				cube([47.5, 26, 2], center=true);
		}
	
		difference()
		{
			translate([-25, 0, -0.5])
					cylinder(r=(26 + 4) / 2, h=2);
		
			translate([-25, 0, -0.5])
					cylinder(r=(26 + 4) / 2 - 3, h=2);
		}
	}
}

module hl2(with_headers)
{
	// PCB
	cube([49, 26, 2], center=true);
	
	// LED matrix
	translate([-49/2 + 20/2 + 10.75, 0, 5.5/2 + 2/2])
		cube([20, 20, 5.5], center=true);
	
	// button 1
	translate([49/2 - 6/2 - 6, 26/2 - 6/2 - 1.5, 3.5/2 + 2/2])
		cube([6, 6, 3.5], center=true);
	
	// button 2
	translate([49/2 - 6/2 - 6, -26/2 + 6/2 + 1.5, 3.5/2 + 2/2])
		cube([6, 6, 3.5], center=true);
	
	// bat holder
	translate([49/2 - 23/2 + 1.6, 0,  -9.5 - 2/2])
		cylinder(r=23/2, h=9.5);
	
	translate([49/2 - 23, 0, -9.5/2 - 2/2])
		cube([4.5, 7.5, 9.5], center=true);

	if(with_headers == 1)
	{
		// header 1
		translate([27, 0, 2.5/2 + 2/2])
			cube([10, 20, 2.5], center=true);
		
		// header 2
		translate([-27, 0, 2.5/2 + 2/2])
			cube([10, 20, 2.5], center=true);
	
	}
}