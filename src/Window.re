type window;

let window: window = [%bs.raw "window"];

[@bs.val] external setTimeout : (unit => unit, int) => int = "";