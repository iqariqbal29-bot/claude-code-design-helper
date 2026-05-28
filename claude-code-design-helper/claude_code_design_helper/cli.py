"""Command-line interface for Claude Code Design Helper."""

import click
from rich.console import Console
from rich.table import Table
from .designer import ProjectDesigner
from .validator import DesignValidator

console = Console()
validator = DesignValidator()


@click.group()
def main():
    """Claude Code Design Helper - AI-assisted code design toolkit."""
    pass


@main.command()
@click.argument("project_name")
@click.option("--language", default="python", help="Project language.")
@click.option("--requirements", "-r", multiple=True, help="Project requirements.")
def design(project_name: str, language: str, requirements):
    """Generate design suggestions for a project."""
    designer = ProjectDesigner(project_name, language)
    suggestions = designer.analyze_requirements(list(requirements))

    table = Table(title=f"Design Suggestions for {project_name}")
    table.add_column("Priority", style="cyan")
    table.add_column("Title", style="green")
    table.add_column("Description", style="white")

    for s in suggestions:
        if validator.is_valid(s):
            table.add_row(str(s.priority), s.title, s.description[:40])

    console.print(table)


@main.command()
@click.argument("title")
@click.argument("description")
@click.option("--priority", default=1, type=int, help="Priority level (1-5).")
@click.option("--tags", "-t", multiple=True, help="Tags for the suggestion.")
def validate(title: str, description: str, priority: int, tags):
    """Validate a design suggestion."""
    from .designer import DesignSuggestion

    suggestion = DesignSuggestion(
        title=title, description=description, priority=priority, tags=list(tags)
    )
    issues = validator.validate(suggestion)

    if issues:
        console.print("[red]Validation failed:[/red]")
        for issue in issues:
            console.print(f"  - {issue}")
    else:
        console.print("[green]Design suggestion is valid![/green]")