# Annotation tags

`@unverified` in a function's `/** */` comment means the function's name (and any description next to it) is a guess that has not yet been confirmed in Stadium Zero by a player agent or a human. Remove the tag once it is confirmed, or rename the function if it turns out wrong.

The text after the tag says where the guess came from:

- `Name from Stadium 1.` The function was ported from the Stadium 1 decomp (team-hippodrome/pokestadium), and that repo has since renamed it. The name was carried over through Stadium 1's symbol history: old name → Stadium 1 address → current name.
- `Name and comment from Stadium 1.` Same, and the description is Stadium 1's comment for that function. Zero has fewer Pokémon and modes, so a list of moves or callers in such a comment may not hold for Zero.
- Anything else describes the evidence the guess was made from.

Find every guess with `grep -rn "@unverified" src`.
