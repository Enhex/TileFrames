#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <pugixml.hpp>
using namespace std;


int main(int argc, char *argv[])
{
	// Make sure enough arguments are given
	if (argc < 4 + 1)
	{
		cout << "Usage: TileFrames <output file> <X tiles> <Y tiles> <framerate> [uv scale] [number of frames]" << endl;
		return 0;
	}

	// Get arguments
	int arg = 0;

	// Output file path
	string output_file_path = argv[++arg];

	// Tiles X
	unsigned tiles_x = stoi(string(argv[++arg]));
	if (tiles_x < 1) { cout << "Error: X tiles must be greater than 0" << endl; }

	// Tiles Y
	unsigned tiles_y = stoi(string(argv[++arg]));
	if (tiles_y < 1) { cout << "Error: Y tiles must be greater than 0" << endl; }

	// Framerate
	float framerate = stof(string(argv[++arg]));

	// Frames
	unsigned frames = numeric_limits<unsigned>::max();
	if (argc > 4 + 1)
		frames = stoi(string(argv[++arg]));

	// Scale
	float scale = 1;
	if(argc > 5 + 1)
		scale = stof(string(argv[++arg]));


	// Converted output XML
	pugi::xml_document output_doc;
	// Time which is incremented for every frame
	float time = 0;

	float u1, v1, u2, v2;
	stringstream ss;

	for (unsigned y = 0; y < tiles_y; ++y)
	{
		if (frames == 0)
			break;

		for (unsigned x = 0; x < tiles_x; ++x)
		{
			if (frames == 0)
				break;

			// UVs
			u1 = (float)x / tiles_x * scale;
			v1 = (float)y / tiles_y * scale;
			u2 = (float)(x + 1) / tiles_x * scale;
			v2 = (float)(y + 1) / tiles_y * scale;

			auto output_child = output_doc.append_child("texanim");
			ss.str(""); ss.clear();
			ss << u1 << ' ' << v1 << ' ' << u2 << ' ' << v2;
			output_child.append_attribute("uv") = ss.str().c_str();

			// time
			ss.str(""); ss.clear();
			ss << time;
			output_child.append_attribute("time") = ss.str().c_str();

			// Increase the time for the next frame
			time += 1 / framerate;

			// Decrease remaining frames count
			--frames;
		}
	}

	// total time
	// TODO should be optional?
	auto output_child = output_doc.prepend_child("TOTAL_TIME");
	ss.str(""); ss.clear();
	ss << time;
	output_child.append_attribute("time") = ss.str().c_str();

	// save document to file
	std::cout << "Saving result: " << output_doc.save_file(output_file_path.c_str(), PUGIXML_TEXT("\t"), pugi::format_indent + pugi::format_no_declaration) << std::endl;
}