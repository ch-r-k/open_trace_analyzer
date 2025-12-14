
\section overview Overview
Open Trace Analyzer is a comprehensive tool for analyzing system trace files. It imports trace data from various sources (such as QSpy trace files), processes task timing information and state machine transitions, and exports the results as sequence diagrams in multiple formats including PlantUML and Open Trace Viewer JSON format.

\section features Key Features
- **Multi-format Import**: Support for text-based trace files and JSON configurations
- **Task Analysis**: Calculates and tracks task timing information and context switches
- **State Machine Support**: Processes and visualizes state machine transitions
- **Multiple Export Formats**: 
  - PlantUML sequence diagrams (timing and standard)
  - Open Trace Viewer JSON format
- **Flexible Configuration**: JSON-based configuration system for input/output control
- **Event Processing**: Parses event messages, task switches, state changes, and notes from traces

\section quickstart Quick Start

\subsection usage Basic Usage
```bash
./open_trace_analyzer <config_file.json>
```

\subsection examples Examples
```bash
# Process trace with PlantUML timing diagram output
./open_trace_analyzer config_puml_timing.json

# Generate Open Trace Viewer visualization
./open_trace_analyzer config_open_trace_viewer.json

# Display help
./open_trace_analyzer --help
```

\section workflow Processing Workflow
1. **Input**: User provides a JSON configuration file specifying input trace file and output format
2. **Parsing**: ApplicationManager parses command-line arguments and configuration
3. **Import**: Trace file is imported and parsed into structured trace entries
4. **Processing**: Task timing calculations and object creation occur
5. **Export**: Results are exported in the requested format (PlantUML or JSON)
6. **Output**: Sequence diagrams or visualization data saved to output file

\section architecture Architecture

\subsection modules Core Modules

- **manager**: Application lifecycle and orchestration
  - `ApplicationManager`: Main entry point, coordinates import/processing/export
  - `ConfigHandler`: Parses and validates JSON configuration files
  - `CommandLineArgHandler`: Processes command-line arguments
  - `UserInputHandler`: Handles user input validation

- **import**: Data import and parsing
  - `ImportTraceFile`: Abstract interface for trace file importers
  - `TxtImporter`: Concrete implementation for text-based trace files (QSpy format)
  - `ImportObject`: Base class for importable trace objects
  - `TxtConfig`: Configuration parser for text trace format
    - Handles: EventMessages, TaskSwitches, StateMachines, Notes

- **types**: Core data structures
  - `TraceEntry`: Base class for all trace events
  - `TaskObject`: Represents a task/object in the system
  - `EventMessage`: Event occurrence in trace
  - `TaskSwitch`: Context switch events
  - `StateMachine`: State machine transitions
  - `Note`: Annotations in trace data

- **application**: Main processing logic
  - `Application`: Coordinates trace processing
  - `TaskTimingCalculator`: Computes timing metrics for tasks

- **export**: Output generation
  - `IExportSequence`: Abstract export interface
  - **PlantUML Export**: Generates PlantUML sequence diagrams
    - `ExportPuml`: Standard sequence diagrams
    - `ExportPumlTiming`: Timing-focused diagrams
  - **Open Trace Viewer Export**: Generates JSON for visualization
    - `OpenTraceViewer`: JSON output formatter

\section configuration Configuration File Format

The tool uses JSON configuration files to specify inputs and outputs:

```json
{
  "input_file": "path/to/trace.txt",
  "input_type": "txt",
  "output_file": "path/to/output",
  "output_type": "puml_timing"
}
```

Supported input types:
- `txt`: Text-based trace files (QSpy format)

Supported output types:
- `puml`: PlantUML standard sequence diagram
- `puml_timing`: PlantUML timing diagram
- `open_trace_viewer`: Open Trace Viewer JSON format


// ...existing code...

\section inputarguments Input Arguments

The application accepts the following command-line arguments:

\subsection args Arguments
- `<config_file>`: Path to the JSON configuration file (required)
  - Specifies input trace file, input type, output file, and output format
- `--help`: Display help message and exit
- `--version`: Display version information and exit

\subsection argexamples Argument Examples
```bash
# Run with configuration file
./open_trace_analyzer /path/to/config.json

# Display help
./open_trace_analyzer --help

# Display version
./open_trace_analyzer --version
```

\section configfile Configuration File Format

The tool uses JSON configuration files to control the import and export process. The configuration file specifies which trace file to analyze and how to export the results.

\subsection configstructure Configuration Structure

```json
{
  "input_file": "path/to/input/trace.txt",
  "input_type": "txt",
  "output_file": "path/to/output/diagram",
  "output_type": "puml_timing"
}
```

\subsection configfields Configuration Fields

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `input_file` | string | Yes | Path to the input trace file to be analyzed |
| `input_type` | string | Yes | Format of the input file (`txt` for QSpy text format) |
| `output_file` | string | Yes | Path where the output file will be written (without extension) |
| `output_type` | string | Yes | Format for the output (`puml`, `puml_timing`, or `open_trace_viewer`) |

\subsection inputtypes Supported Input Types

- **`txt`**: Text-based trace files
  - Expected format: QSpy trace file format
  - Contains task switches, state machines, events, and notes

\subsection outputtypes Supported Output Types

- **`puml`**: PlantUML standard sequence diagram
  - Generates `.txt` file with PlantUML syntax
  - Shows interactions between tasks/objects as a sequence diagram

- **`puml_timing`**: PlantUML timing diagram
  - Generates `.txt` file with PlantUML timing diagram syntax
  - Displays timing relationships and task execution periods

- **`open_trace_viewer`**: Open Trace Viewer JSON format
  - Generates `.json` file compatible with Open Trace Viewer
  - Suitable for interactive visualization

\subsection configexamples Configuration File Examples

\subsubsection example1 Example 1: PlantUML Timing Diagram

```json
{
  "input_file": "traces/qspy_01.txt",
  "input_type": "txt",
  "output_file": "output/timing_diagram",
  "output_type": "puml_timing"
}
```

\subsubsection example2 Example 2: Open Trace Viewer Format

```json
{
  "input_file": "traces/embedded_system.txt",
  "input_type": "txt",
  "output_file": "output/trace_visualization",
  "output_type": "open_trace_viewer"
}
```

\subsubsection example3 Example 3: Standard Sequence Diagram

```json
{
  "input_file": "traces/system_trace.txt",
  "input_type": "txt",
  "output_file": "output/sequence",
  "output_type": "puml"
}
```

\subsection configerrors Configuration Validation

The application validates the configuration file and will report errors for:
- Missing required fields
- Invalid input type (not `txt`)
- Invalid output type (not `puml`, `puml_timing`, or `open_trace_viewer`)
- Non-existent input files
- Invalid file paths for output


\section building Building the Project

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run tests
make test
```

\section testing Testing

Unit tests are included throughout the codebase:
- Configuration validation tests
- Command-line argument parsing tests
- Trace import tests
- System integration tests

Run tests with:
```bash
cd build
ctest --output-on-failure
```

\section extending Extending the Tool

To add a new import format:
1. Create a new class inheriting from `IImportTrace`
2. Implement the import logic
3. Register in `ApplicationManager`

To add a new export format:
1. Create a new class inheriting from `IExportSequence`
2. Implement the export logic
3. Register in `ApplicationManager`

\section license License
[Add your license information]
