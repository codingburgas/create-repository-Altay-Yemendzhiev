# Conventional Commits

This project uses short imperative commit messages based on the Conventional
Commits style.

## Format

```text
type(optional-scope): short description
```

## Allowed Types

- `feat`: add a user-facing feature
- `fix`: fix a bug
- `docs`: documentation-only change
- `style`: formatting-only change
- `refactor`: restructure code without changing behavior
- `build`: CMake, dependency, or build setup change
- `test`: add or update tests
- `chore`: repository cleanup or maintenance

## Examples

```text
feat(ui): add product table filtering
fix(data): handle empty csv rows
docs: update build instructions
refactor(structure): organize project layers
build: switch gui target to qt widgets
```

Use present-tense imperative wording, such as `add`, `fix`, `update`, or
`organize`.
