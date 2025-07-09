# Task 1: Block Placement

1. **add_block**  
   - Validates the target coordinates (x, y, z) against the chunk’s dimensions.  
   - If the coordinates are in range, writes the block value directly into the 3D array.  
   - Returns the updated chunk to confirm successful placement.

---

# Task 2: Parallelepiped Fill

1. Determine the minimum and maximum coordinates on each axis by comparing the two corner points.  
2. Clamp those bounds to the chunk’s limits to avoid out-of-range access.  
3. Use three nested loops over X, Y, and Z:  
   - Outer loop over X  
   - Middle loop over Y (for each X)  
   - Inner loop over Z (for each X, Y)  
4. For each (X, Y, Z) inside the bounds, assign the specified block value.

---

# Task 3: Sphere Fill

1. Define a bounding box around the sphere based on its radius.  
2. For each point in the box, compute the squared Euclidean distance to the sphere’s center.  
3. If distance_squared < radius², it lies inside the sphere—assign the block value.  
4. Iterate with three nested loops over X, Y, Z in the bounding box.  
5. At the end, apply the same boundary checks as in Task 2 to respect chunk limits.

---

# Task 4: Shell Around Target Block

1. Copy the original chunk to avoid in-place overwrites during iteration.  
2. Scan every block in the chunk:  
   - If it matches target_block, examine its neighbors.  
   - For each neighbor position, place a shell_block.  
3. Use three nested loops around (dx, dy, dz) offsets to cover all adjacent positions.

---

# Task 5: 2D Flood Fill in the X–Z Plane

1. Mark the starting position as processed and assign the new block.  
2. Push neighbor coordinates (up, down, left, right) in the X–Z plane into a stack if they match the initial block type.  
3. Repeat iteratively until the stack is empty.  
4. Finally, manage memory by reallocating or freeing the 2D slice as needed.

---

# Task 6: 3D Flood Fill

1. Validate the starting coordinates and check the block matches the target.  
2. Mark the current position as visited and assign the new block.  
3. Push all six neighbors into the stack if they’re in bounds and match the target block.  
4. Continue until all connected positions are processed.  
5. Free any allocated memory, following the same pattern as Task 5.

---

# Task 7: Rotation Around the Y-Axis

1. Dynamically allocate a new chunk with swapped width ↔ depth.  
2. Iterate over the original 3D array with three nested loops (X, Y, Z).  
3. Compute new coordinates for each block:  
   - newX = originalDepth – 1 – Z  
   - newZ = originalX  
   - newY = originalY  
4. Copy values into the new chunk at (newX, newY, newZ).  
5. Free the original chunk’s memory.
