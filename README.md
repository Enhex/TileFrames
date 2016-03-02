# TileFrames
Tool for creating `Urho3D::ParticleEffect` frames for tiled spritesheets.

Creates an XML file containing the `<texanim>` nodes. Copy them into your particle effect XML.
A special `<TOTAL_TIME>` node is prepended which gives you the total animation time, so you don't have to manually calculate it.

### Usage
`TileFrames <output file> <X tiles> <Y tiles> <framerate> [uv scale] [number of frames]`
