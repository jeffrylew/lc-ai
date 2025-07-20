def is_loc_valid(
    self,
    row: int,
    col: int,
    total_rows: int,
    total_cols: int,
) -> bool:
    """Checks if loc at (row, col) is within the grid."""
    return 0 <= row < total_rows and 0 <= col < total_cols


def discover_island(
    self,
    row: int,
    col: int,
    total_rows: int,
    total_cols: int,
    grid: List[List[str]],
    visited_locs: Set[Tuple[int, int]],
) -> None:
    """Perform DFS to find land locs within an island starting from row, col."""
    loc_stack: List[Tuple[int, int]] = [(row, col)]

    neighbor_locs: List[Tuple[int, int]] = [(-1, 0), (0, -1), (1, 0), (0, 1)]

    while loc_stack:
        curr_loc = loc_stack.pop()
        curr_row, curr_col = curr_loc

        if curr_loc in visited_locs:
            continue

        visited_locs.add(curr_loc)

        for drow, dcol in neighbor_locs:
            next_row, next_col = curr_row + drow, curr_col + dcol

            if not self.is_loc_valid(
                next_row,
                next_col,
                total_rows,
                total_cols
            ):
                continue

            if grid[next_row][next_col] is "0":
                continue

            loc_stack.append((next_row, next_col))


def numIslandsFA(self, grid: List[List[str]]) -> int:
    num_islands: int = 0
    total_rows: int = len(grid)
    total_cols: int = len(grid[0])

    visited_locs: Set[Tuple[int, int]] = set()

    for row_idx, row in enumerate(grid):
        for col_idx, water_or_land in enumerate(row):
            if water_or_land == "0":
                continue

            if (row_idx, col_idx) in visited_locs:
                continue

            num_islands += 1

            self.discover_island(
                row_idx,
                col_idx,
                total_rows,
                total_cols,
                grid,
                visited_locs,
            )

    return num_islands


def numIslandsDS1(self, grid: List[List[str]]) -> int:
    """
    Time complexity O(M x N), where M = num rows and N = num cols.
    Space complexity O(M x N) in the worst case that the grid map is filled with
    lands where DFS is M x N deep.
    """
    if not grid:
        return 0

    num_islands = 0
    for row in range(len(grid)):
        for col in range(len(grid[0])):
            if grid[row][col] == "1":
                self.mark_island(grid, row, col)
                num_islands += 1

    return num_islands


def mark_island(self, grid, row, col):
    if (
        row < 0
        or col < 0
        or row >= len(grid)
        or col >= len(grid[0])
        or grid[row][col] != "1"
    ):
        return

    grid[row][col] = "0"

    self.mark_island(grid, row - 1, col)
    self.mark_island(grid, row + 1, col)
    self.mark_island(grid, row, col - 1)
    self.mark_island(grid, row, col + 1)
